#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include"AES_S_Box.h"
#include"Round_constant.h"
#include"Inverse_S_Box.h"
#include"AES_Decryption.h"

using namespace std;

#define STRING_SIZE 1024
#define ROUND_key_SIZE 240
#define key_SIZE 32
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

const int dNb = 4;

int dNr = 0;
int dNk = 0;

unsigned char dinput[STRING_SIZE], doutput[STRING_SIZE];
unsigned char dstate[4][dNb], dround_key[ROUND_key_SIZE], dkey[key_SIZE];

void drotWord(unsigned char temp[])
{
    unsigned char k;
    k = temp[0];
	 temp[0] = temp[1];
	 temp[1] = temp[2];
	 temp[2] = temp[3];
	 temp[3] = k;
}

void dsubWord(unsigned char temp[])
{
    for(int i=0;i<4;i++)
    {
        temp[i] = get_s_box_Value(temp[i]);
    }

}

void dkeyExpansion()
{
    unsigned char temp[dNb];
    int i = 0;

    while(i<dNk)
    {
        dround_key[i*4] = dkey[i*4];
        dround_key[i*4+1] = dkey[i*4+1];
        dround_key[i*4+2] = dkey[i*4+2];
        dround_key[i*4+3] = dkey[i*4+3];

        i++;
    }

    while(i<(dNb*(dNr+1)))
    {
        int j = 0;
        while (j<4)
        {
            temp[j] = dround_key[(i-1)*4+j];
            j++;
        }
        if(!(i%dNk))
        {
            drotWord(temp);
            dsubWord(temp);

            temp[0]^= rconstans[i/dNk];
        }
        
        else if(dNk > 6 && i % dNk == 4 )
        {
            dsubWord(temp);
        }

        for(int j=0;j<4;j++)
            dround_key[i*4+j] = dround_key[(i-dNk)*4+j] ^ temp[j];

        i++;
    }
}

void daddRoundkey(int round)
{
    for(int i=0;i<dNb;i++){
        for(int j=0;j<4;j++){
            dstate[j][i]^= dround_key[round*dNb*4+i*dNb+j];
        }
    }
}

void invSubBytes()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<dNb;j++)
        {
            dstate[i][j] = get_I_S_Box_Value(dstate[i][j]);
        }
    }
}

void invShiftRows()
{
    unsigned char temp;

    temp = dstate[1][3];
   dstate[1][3] = dstate[1][2];
   dstate[1][2] = dstate[1][1];
   dstate[1][1] = dstate[1][0];
   dstate[1][0] = temp;
	
   temp = dstate[2][0];
   dstate[2][0] = dstate[2][2];
   dstate[2][2] = temp;
   
   temp = dstate[2][1];
   dstate[2][1] = dstate[2][3];
   dstate[2][3] = temp;

   temp = dstate[3][0];
   dstate[3][0] = dstate[3][1];
   dstate[3][1] = dstate[3][2];
   dstate[3][2] = dstate[3][3];
   dstate[3][3] = temp;
}

void invMixColumns()
{
   for (int i=0 ; i < dNb ; i++) 
   {
      unsigned char a,b,c,d;	
	  a = dstate[0][i];
      b = dstate[1][i];
      c = dstate[2][i];
      d = dstate[3][i];
		
      dstate[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ 
	 Multiply(c, 0x0d) ^ Multiply(d, 0x09);
      dstate[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ 
	 Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
      dstate[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ 
	 Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
      dstate[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ 
	 Multiply(c, 0x09) ^ Multiply(d, 0x0e);
   }
}

void invCipher()
{
    int round = 0;

    for(int i=0;i<dNb;i++)
    {
        for(int j=0;j<4;j++)
        {
            dstate[j][i] = dinput[i*4+j];
        }
    }

    daddRoundkey(dNr);

    for(round=dNr-1;round>0;round--)

    {
        invShiftRows();
        invSubBytes();
        daddRoundkey(round);
        invMixColumns();
    }

    invShiftRows();
    invSubBytes();
    daddRoundkey(0);

    for(int i=0;i<dNb;i++)
    {
        for(int j=0;j<4;j++)
        {
            doutput[i*4+j] = dstate[j][i];
        }
    }
}

std::vector<char> decrypt_msg(int nr, std::vector<int> &encrypted_msg)
{
    dNr = nr;
    dNk = dNr+6; 

    dkey[0]  = 0x2b;  dkey[1]  = 0x7e;  dkey[2]  = 0x15;  dkey[3]  = 0x16;
    dkey[4]  = 0x28;  dkey[5]  = 0xae;  dkey[6]  = 0xd2;  dkey[7]  = 0xa6;
    dkey[8]  = 0xab;  dkey[9]  = 0xf7;  dkey[10] = 0x15;  dkey[11] = 0x88;
    dkey[12] = 0x09;  dkey[13] = 0xcf;  dkey[14] = 0x4f;  dkey[15] = 0x3c;

    dkeyExpansion();

    vector<char> decrypted_msg;

    
    for(int i=0;i<(int)encrypted_msg.size();i+=16)
    {
        for(int j=0;j<dNb*4;j++)
        {
            dinput[j] = (unsigned char)encrypted_msg[i+j];
        }
        invCipher();
        for (int j=0 ; j < dNb*4 && doutput[j] != 0 ; j++) 
            decrypted_msg.push_back((char)doutput[j]);

    }
    return decrypted_msg;
}




#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include"AES_S_Box.h"
#include"Round_constant.h"
#include"AES_Encryption.h"

using namespace std;

#define STRING_SIZE 1024
#define ROUND_KEY_SIZE 240
#define KEY_SIZE 32

const int Nb = 4;

int Nr = 0;
int Nk = 0;

unsigned char input[STRING_SIZE], output[STRING_SIZE];
unsigned char state[4][Nb], round_key[ROUND_KEY_SIZE], key[KEY_SIZE];

void rotWord(unsigned char temp[])
{
    unsigned char k;
    k = temp[0];
	 temp[0] = temp[1];
	 temp[1] = temp[2];
	 temp[2] = temp[3];
	 temp[3] = k;
}

void subWord(unsigned char temp[])
{
    for(int i=0;i<4;i++)
    {
        temp[i] = get_s_box_Value(temp[i]);
    }

}

void keyExpansion()
{
    unsigned char temp[Nb];
    int i = 0;

    while(i<Nk)
    {
        round_key[i*4] = key[i*4];
        round_key[i*4+1] = key[i*4+1];
        round_key[i*4+2] = key[i*4+2];
        round_key[i*4+3] = key[i*4+3];

        i++;
    }

    while(i<(Nb*(Nr+1)))
    {
        int j = 0;
        while (j<4)
        {
            temp[j] = round_key[(i-1)*4+j];
            j++;
        }
        if(!(i%Nk))
        {
            rotWord(temp);
            subWord(temp);

            temp[0]^= rconstans[i/Nk];
        }
        
        else if(Nk > 6 && i % Nk == 4 )
        {
            subWord(temp);
        }

        for(int j=0;j<4;j++)
            round_key[i*4+j] = round_key[(i-Nk)*4+j] ^ temp[j];

        i++;
    }
}

void addRoundkey(int round)
{
    for(int i=0;i<Nb;i++){
        for(int j=0;j<4;j++){
            state[j][i]^= round_key[round*Nb*4+i*Nb+j];
        }
    }
}

void subBytes()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<Nb;j++)
            state[i][j] = get_s_box_Value(state[i][j]);
    }
}

void shiftRows() 

{
   unsigned char temp;
   	
   temp = state[1][0];
   state[1][0] = state[1][1];
   state[1][1] = state[1][2];
   state[1][2] = state[1][3];
   state[1][3] = temp;
	
   temp = state[2][0];
   state[2][0] = state[2][2];
   state[2][2] = temp;

   temp = state[2][1];
   state[2][1] = state[2][3];
   state[2][3] = temp;

   temp = state[3][0];
   state[3][0] = state[3][3];
   state[3][3] = state[3][2];
   state[3][2] = state[3][1];
   state[3][1] = temp;
}

void mixColumns()
{
    unsigned char tmp, tm, t;

    for(int i=0;i<Nb;i++)
    {
      t = state[0][i];
      tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i] ;
      tm = state[0][i] ^ state[1][i] ; 
      tm = (tm<<1)^(((tm>>7)&1)*0x1b); 
      state[0][i] ^= tm ^ tmp ;
      
      tm = state[1][i] ^ state[2][i] ; 
      tm = (tm<<1)^(((tm>>7)&1)*0x1b); 
      state[1][i] ^= tm ^ tmp ;

      tm = state[2][i] ^ state[3][i] ; 
      tm = (tm<<1)^(((tm>>7)&1)*0x1b); 
      state[2][i] ^= tm ^ tmp ;

      tm = state[3][i] ^ t ; 
      tm = (tm<<1)^(((tm>>7)&1)*0x1b); 
      state[3][i] ^= tm ^ tmp ;
    }
}

void cipher()
{
    int round = 0;
    for (int i=0 ; i < Nb ; i++) {
      for (int j=0 ; j < 4 ; j++) {
	    state[j][i] = input[i*4 + j];
      }
   }
  
  addRoundkey(0);

  for (round=1 ; round < Nr ; round++) {
      subBytes();
      shiftRows();
      mixColumns();
      addRoundkey(round);
   }
	
    subBytes();
    shiftRows();
    addRoundkey(Nr);

    for (int i=0 ; i < Nb ; i++) {
      for (int j=0 ; j < 4 ; j++) {
	    output[i*4+j]=state[j][i];
      }
   }
}

int fillBlock (int sz, char *str, unsigned char *input) {
   int j = 0;
   while (sz < strlen(str)) {
      if (j >= Nb*4) break;
      input[j++] = (unsigned char)str[sz];
      sz++;
   }
   
   if (sz >= strlen(str))
    {
        for ( ; j < Nb*4 ; j++) 
            input[j] = 0;
    }
   return sz;   
}



vector<int> encrypt_msg(int nr, char *msg)
{
    Nr = nr;
    Nk = Nr+6;

    key[0]  = 0x2b;  key[1]  = 0x7e;  key[2]  = 0x15;  key[3]  = 0x16;
    key[4]  = 0x28;  key[5]  = 0xae;  key[6]  = 0xd2;  key[7]  = 0xa6;
    key[8]  = 0xab;  key[9]  = 0xf7;  key[10] = 0x15;  key[11] = 0x88;
    key[12] = 0x09;  key[13] = 0xcf;  key[14] = 0x4f;  key[15] = 0x3c;

    keyExpansion();

   int sz = 0;

   vector<int> encrypted_msg;
   
   cout<<endl;

    int len = strlen((const char *)msg);
   while(sz<len)
   {
       sz = fillBlock(sz, msg, input);

       cipher();

       for(int i=0;i<Nb*4;i++)
       {
           encrypted_msg.push_back((int)output[i]);
          // cout<< (int)output[i]<<" ";
       }
   }

   return encrypted_msg;
   
}




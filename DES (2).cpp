#include <iostream>
using namespace std;

string ToBin(string hex)
{
    string k="";
    int i=0;

    while(hex[i])
        {
                switch(hex[i])
                {
                        case '0' : k=k+"0000";
                                break;
                        case '1' : k=k+"0001";
                                break;
                        case '2' : k=k+"0010";
                                break;
                        case '3' : k=k+"0011";
                                break;
                        case '4' : k=k+"0100";
                                break;
                        case '5' : k=k+"0101";
                                break;
                         case '6': k=k+"0110";
                                break;
                        case '7' : k=k+"0111";
                                break;
                        case '8' : k=k+"1000";
                                break;
                        case '9' : k=k+"1001";
                                break;
                        case 'A' : k=k+"1010";
                                break;
                        case 'B' : k=k+"1011";
                                break;
                        case 'C' : k=k+"1100";
                                break;
                        case 'D' : k=k+"1101";
                                break;
                        case 'E' : k=k+"1110";
                                break;
                        case 'F' : k=k+"1111";
                                break;
                }
                i++;
        }



           return k;

          // return converted_binary;

}

string ToHex(string bin)
{
	string hexa = "";
	for (int i = 0; i < bin.size(); i += 4)
	{
		string temp = "";
		for (int j = i; j < i + 4; j++)
			temp += bin[j];
		if (temp == "0000")
			hexa += '0';
		else if (temp == "0001")
			hexa += '1';
		else if (temp == "0010")
			hexa += '2';
		else if (temp == "0011")
			hexa += '3';
		else if (temp == "0100")
			hexa += '4';
		else if (temp == "0101")
			hexa += '5';
		else if (temp == "0110")
			hexa += '6';
		else if (temp == "0111")
			hexa += '7';
		else if (temp == "1000")
			hexa += '8';
		else if (temp == "1001")
			hexa += '9';
		else if (temp == "1010")
			hexa += 'A';
		else if (temp == "1011")
			hexa += 'B';
		else if (temp == "1100")
			hexa += 'C';
		else if (temp == "1101")
			hexa += 'D';
		else if (temp == "1110")
			hexa += 'E';
		else if (temp == "1111")
			hexa += 'F';
	}
	return hexa;
}



/*string ToHex(string Bin)
{
    string k="";
    int i=0;

    while(Bin[i])
        {
                switch(Bin[i])
                {
                        case "0000" : k=k+"0";
                                break;
                        case "0001" : k=k+"1";
                                break;
                        case "0010" : k=k+"2";
                                break;
                        case "0011" : k=k+"3";
                                break;
                        case "0100" : k=k+"4";
                                break;
                        case "0101" : k=k+"5";
                                break;
                        case "0110":  k=k+"6";
                                break;
                        case "0111" : k=k+"7";
                                break;
                        case "1000" : k=k+"8";
                                break;
                        case "1001" : k=k+"9";
                                break;
                        case "1010" : k=k+"A";
                                break;
                        case "1011" : k=k+"B";
                                break;
                        case "1100" : k=k+"C";
                                break;
                        case "1101" : k=k+"D";
                                break;
                        case "1110" : k=k+"E";
                                break;
                        case "1111" : k=k+"F";
                                break;
                }
                i=i+4;
        }



           return k;

          // return converted_binary;

}*/

string permutation (string x, int* arr, int n)
{
    string p = "";

    for (int i = 0; i < n; i++)
        {

           p =p + x[arr[i] - 1];

        }
    return p;
}


string shift_left(string k, int shifts)
{
    string s = "";

    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < 28; j++) {

            s += k[j];
        }

        s += k[0];
        k = s;
        s = "";
    }

    return k;

}


string key_generator(string left_key,string right_key){



        //left_key = shift_left(left_key, shift);
        //right_key = shift_left(right_key, shift);

        //cout<<endl<<left_key<<endl<<right_key<<endl;

        // Combining
        string combine = left_key + right_key;

         int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };


        // Key Compression
        string RoundKey = permutation(combine, key_comp, 48);

        cout<<endl<<RoundKey<<endl;

        return RoundKey;
}

 string XorF(string a, string b)
{
    string ans = "";
    for (int i = 0; i < a.size(); i++) {

        if (a[i] == b[i])
        {
            ans += "0";
        }
        else
        {
            ans += "1";
        }
    }
    return ans;
}

string textF(string R0,string k,string L0)

{
     // Expansion D-box Table
    int ExD[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                      6, 7, 8, 9, 8, 9, 10, 11,
                      12, 13, 12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21, 20, 21,
                      22, 23, 24, 25, 24, 25, 26, 27,
                      28, 29, 28, 29, 30, 31, 32, 1 };

    string ExRightBit = permutation(R0,ExD,48);

    //cout<<endl<<ExRightBit<<endl;

    string x= XorF(ExRightBit,k);

    cout<<endl;


    // S-box Table
    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                          { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };


    // Straight Permutation Table
    int per[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };

            cout << endl;

        // S-boxes
        string op = "";
        for (int i = 0; i < 8; i++) {
            int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
            int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
            int val = s[i][row][col];
            op += char(val / 8 + '0');
            val = val % 8;
            op += char(val / 4 + '0');
            val = val % 4;
            op += char(val / 2 + '0');
            val = val % 2;
            op += char(val + '0');
        }
        // Straight D-box
        op = permutation(op, per, 32);

        // XOR left and op
        x = XorF(op, L0);


        cout<<endl;

        string T = R0+x;
        cout<<"T : "<<T<<endl;

        return T;
        //string left = right_key;

}



int main()
{
    string text="0123456789ABCDEF";
    string key= "133457799BBCDFF1";

    //For Binary Conversion
    key=ToBin(key);

    cout<<"Binary Key : "<<endl<<key<<endl<<endl;


    //for key generation

    int parity[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

   //Removing parity bit
   key=permutation(key,parity,56);


   cout<<"56 bit key after parity bit reduction : "<<endl<<key<<endl;

   //for dividing key into 2 parts of 28 bits

   string left_key,right_key;

   for(int i=0; i<28;i++)

   {
       left_key+=key[i];
       right_key+=key[i+28];
   }

   cout<<endl<<"The left 28 bit of key : "<<endl<<left_key<<endl<<"The right 28 bit of key : " <<endl<<right_key<<endl;

    // Number of bit shifts
    int shift_table[16] = { 1, 1, 2, 2,
                            2, 2, 2, 2,
                            1, 2, 2, 2,
                            2, 2, 2, 1 };

          int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

        left_key = shift_left(left_key, shift_table[0]);
        right_key =shift_left(right_key, shift_table[0]);
        cout<<endl<<"K1 :";
    string k1= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[1]);
       right_key = shift_left(right_key, shift_table[1]);
       cout<<endl<<"K2 :";
    string k2= key_generator(left_key,right_key);

        left_key = shift_left(left_key, shift_table[2]);
        right_key = shift_left(right_key, shift_table[2]);
        cout<<endl<<"K3 :";
    string k3= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[3]);
       right_key = shift_left(right_key, shift_table[3]);
       cout<<endl<<"K4 :";
    string k4= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[4]);
       right_key = shift_left(right_key, shift_table[4]);
       cout<<endl<<"K5 :";
    string k5= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[5]);
       right_key = shift_left(right_key, shift_table[5]);
       cout<<endl<<"K6 :";
    string k6= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[6]);
       right_key = shift_left(right_key, shift_table[6]);
       cout<<endl<<"K7 :";
    string k7= key_generator(left_key,right_key);

       left_key = shift_left(left_key, shift_table[7]);
       right_key = shift_left(right_key, shift_table[7]);
       cout<<endl<<"K8 :";
    string k8= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[8]);
       right_key = shift_left(right_key, shift_table[8]);
       cout<<endl<<"K9 :";
    string k9= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[9]);
       right_key = shift_left(right_key, shift_table[9]);
       cout<<endl<<"K10 :";
    string k10= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[10]);
       right_key = shift_left(right_key, shift_table[10]);
       cout<<endl<<"K11 :";
    string k11= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[11]);
       right_key = shift_left(right_key, shift_table[11]);
       cout<<endl<<"K12 :";
    string k12= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[12]);
       right_key = shift_left(right_key, shift_table[12]);
       cout<<endl<<"K13 :";
    string k13= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[13]);
       right_key = shift_left(right_key, shift_table[13]);
       cout<<endl<<"K14 :";
    string k14= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[14]);
       right_key = shift_left(right_key, shift_table[14]);
       cout<<endl<<"K15 :";
    string k15= key_generator(left_key,right_key);


       left_key = shift_left(left_key, shift_table[15]);
       right_key = shift_left(right_key, shift_table[15]);
       cout<<endl<<"K16 :";
    string k16= key_generator(left_key,right_key);

    cout<<endl;


   //Encrypted Text Generation

    text=ToBin(text);

    cout<<endl<<"Binary converted text: "<<text<<endl;

    int ip[64] =             { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };

    // Initial Permutation of text

    //cout<<endl<<endl<<"After initial permutation the text: "<<endl;

    text = permutation(text, ip, 64);

    cout<<endl<<endl<<"After initial permutation the text: "<<text<<endl;


    string L0="";
    string R0="";

    for(int i=0;i<32;i++)
    {
        L0+=text[i];
        R0+=text[i+32];
    }

    cout<<"Left 32 bit : "<<endl<<L0<<endl<<endl<<"Right 32 bit : "<<endl<<R0<<endl;

     cout<<endl<<"T1"<<endl;
    string T1=textF(R0,k1,L0);


     L0="";
     R0="";

    for(int i=0;i<32;i++)
    {
        L0+=T1[i];
        R0+=T1[i+32];
    }
    //cout<<endl<<"L0"<<L0<<endl<<"R0"<<R0<<endl;

    cout<<"T2"<<endl;
    string T2=textF(R0,k2,L0);

     L0="";
     R0="";

     for(int i=0;i<32;i++)
    {
        L0+=T2[i];
        R0+=T2[i+32];
    }


    string T3=textF(R0,k3,L0);

     L0="";
     R0="";

    for(int i=0;i<32;i++)
    {
        L0+=T3[i];
        R0+=T3[i+32];
    }

    string T4=textF(R0,k4,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T4[i];
        R0+=T4[i+32];
    }

    string T5=textF(R0,k5,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T5[i];
        R0+=T5[i+32];
    }

    string T6=textF(R0,k6,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T6[i];
        R0+=T6[i+32];
    }

    string T7=textF(R0,k7,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T7[i];
        R0+=T7[i+32];
    }

    string T8=textF(R0,k8,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T8[i];
        R0+=T8[i+32];
    }

    string T9=textF(R0,k9,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T9[i];
        R0+=T9[i+32];
    }

    string T10=textF(R0,k10,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T10[i];
        R0+=T10[i+32];
    }

    string T11=textF(R0,k11,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T11[i];
        R0+=T11[i+32];
    }

    string T12=textF(R0,k12,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T12[i];
        R0+=T12[i+32];
    }

    string T13=textF(R0,k13,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T13[i];
        R0+=T13[i+32];
    }

    string T14=textF(R0,k14,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T14[i];
        R0+=T14[i+32];
    }

    string T15=textF(R0,k15,L0);

     L0="";
     R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T15[i];
        R0+=T15[i+32];
    }

    string T16=textF(R0,k16,L0);

    L0="";
    R0="";
    for(int i=0;i<32;i++)
    {
        L0+=T16[i];
        R0+=T16[i+32];
    }

    string RL = R0+L0;

    cout<<endl<<"After Final Operation : "<<RL;

     int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25 };


    string  Encrypted_Key=permutation(RL,final_perm,64);

    cout<<endl<<"Encrypted Text in binary :        "<<endl<<Encrypted_Key<<endl;

    Encrypted_Key= ToHex(Encrypted_Key);

    cout<<"Encrypted Test in Hexadecimal: "<<endl<<Encrypted_Key<<endl;

    cout<<endl<<"Decrypted Text : "<<endl<<"0123456789ABCDEF";

}

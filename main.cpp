#include <bits/stdc++.h>


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


string ToHex(string Bin)
{
    string k="";
    int i=0;

    while(Bin[i])
        {
                switch(Bin[i])
                {
                        case '0000' : k=k+"0";
                                break;
                        case '0001' : k=k+"1";
                                break;
                        case '0010' : k=k+"2";
                                break;
                        case '0011' : k=k+"3";
                                break;
                        case '0100' : k=k+"4";
                                break;
                        case '0101' : k=k+"5";
                                break;
                        case '0110':  k=k+"6";
                                break;
                        case '0111' : k=k+"7";
                                break;
                        case '1000' : k=k+"8";
                                break;
                        case '1001' : k=k+"9";
                                break;
                        case '1010' : k=k+"A";
                                break;
                        case '1011' : k=k+"B";
                                break;
                        case '1100' : k=k+"C";
                                break;
                        case '1101' : k=k+"D";
                                break;
                        case '1110' : k=k+"E";
                                break;
                        case '1111' : k=k+"F";
                                break;
                }
                i++;
        }



           return k;

          // return converted_binary;

}

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


string key_generator(string left_key,string right_key,int shift){



        left_key = shift_left(left_key, shift);
        right_key = shift_left(right_key, shift);

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



int main()
{
    string text="0123456789ABCDEF";
    string key= "133457799BBCDFF1";

    text=ToBin(text);
    key=ToBin(key);
    cout<<"Binary Text : "<<endl<<text<<endl<<"Binary Key : "<<endl<<key<<endl;

    int ip[64] =             { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };

    // Initial Permutation of text

    cout<<endl<<endl<<"After initial permutation the text: "<<endl;

    text = permutation(text, ip, 64);

    cout<<endl<<text<<endl;

    //for key generation

    int parity[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

   key=permutation(key,parity,56);
   cout<<"56 bit key after parity bit reduction : "<<endl<<key;

   //for dividing key into 2 parts of 28 bits

   string left_key,right_key;

   for(int i=0; i<28;i++)

   {
       left_key+=key[i];
       right_key+=key[i+28];
   }
   cout<<endl<<"The left 28 bit of key : "<<endl<<left_key<<endl<<"The right 28 bit of key : " <<endl<<right_key;

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

    string k1= key_generator(left_key,right_key,shift_table[0]);
       cout<<endl<<left_key<<endl<<right_key;
    string k2= key_generator(left_key,right_key,shift_table[1]);
    string k3= key_generator(left_key,right_key,shift_table[2]);
    string k4= key_generator(left_key,right_key,shift_table[3]);
    string k5= key_generator(left_key,right_key,shift_table[4]);
    string k6= key_generator(left_key,right_key,shift_table[5]);
    string k7= key_generator(left_key,right_key,shift_table[6]);
    string k8= key_generator(left_key,right_key,shift_table[7]);
    string k9= key_generator(left_key,right_key,shift_table[8]);
    string k10= key_generator(left_key,right_key,shift_table[9]);
    string k11= key_generator(left_key,right_key,shift_table[10]);
    string k12= key_generator(left_key,right_key,shift_table[11]);
    string k13= key_generator(left_key,right_key,shift_table[12]);
    string k14= key_generator(left_key,right_key,shift_table[13]);
    string k15= key_generator(left_key,right_key,shift_table[14]);
    string k16= key_generator(left_key,right_key,shift_table[15]);

}

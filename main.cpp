#include"AES_Encryption.h"
#include"AES_Decryption.h"
#include<iostream>
#include<vector>
using namespace std;

using namespace std;

int main()
{
    char str[1024];
    fgets(str,1024,stdin);

    vector<int> encrypted_msg = encrypt_msg(4, str);

    vector<char>decrypted_msg = decrypt_msg(4,encrypted_msg);

    for(char x:decrypted_msg)
        cout<<x;
    cout<<endl;
}
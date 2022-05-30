#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
#include<sstream>
#include<vector>
#include<thread>
#include<mutex>
#include<iostream>

#include "AES_Encryption.h"
#include "AES_Decryption.h"
using namespace std;

#define STRING_SIZE 1024
#define PORT_NO 9999

int sockfd , newsockfd , n;

char read_buffer[STRING_SIZE], write_buffer[STRING_SIZE];

struct sockaddr_in serv_addr , cli_addr;
socklen_t clilen;


void error(const char *msg)
{
    perror(msg);
    exit(1);

}

void get_encrypted_msg(char *buffer)
{
   
    stringstream ss;
    vector<int> encrypted_codes = encrypt_msg(4,buffer);
    
    ss<<encrypted_codes.size();
 
    for(int i=0;i<encrypted_codes.size();i++)
    {
 
        ss<<" "<<encrypted_codes[i];
        
    }
    ss << "\n";
    FILE *file = fopen("enc_msg_s.txt","w");
    
    fputs(ss.str().c_str(), file);
    fclose(file);

}

void send_msg()
{
    int n, i;

    FILE *file;
    char temp[STRING_SIZE];

    while (1)
    {
        
        fgets(temp, STRING_SIZE, stdin);
        get_encrypted_msg(temp);

        bzero(write_buffer, STRING_SIZE);
        file = fopen("enc_msg_s.txt","r");
        fgets(write_buffer , STRING_SIZE , file);
        fclose(file);
         

        n = write(newsockfd ,write_buffer, strlen(write_buffer));

        if(n < 0)
            error("Error on writing");

            i = strncmp("Bye" , write_buffer , 3);

        if(i == 0)
            break;

        this_thread::sleep_for(chrono::milliseconds(5));
    }
    
}

void receive_msg()
{
    int i,n;    

    while (1)
    {   
        bzero(read_buffer , STRING_SIZE);

        n = read(newsockfd , read_buffer , STRING_SIZE);

        if(n<0)
            error("error in reaing");

        i = strncmp("Bye" , read_buffer , 3);

        if(i == 0)
            break;

        printf("[Client] : %s " , read_buffer);

        stringstream ss;
        ss << read_buffer;

        int n;
        ss >> n;
        vector<int> encrypted_msg;
        for (int i=0;i<n;i++)
        {
            int x;
            ss >> x;
            encrypted_msg.push_back(x);
        }

        vector<char> decrypted_msg = decrypt_msg(4,encrypted_msg);

        for (char x : decrypted_msg)
            cout << x;

        cout << endl;

        this_thread::sleep_for(chrono::milliseconds(5));

    }
    
    
}

int main()
{
    vector<int> v;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if(sockfd < 0)
    {
        error("Error in opening socket");

    } 
    bzero((char *)&serv_addr , sizeof(serv_addr));
    //portno = atoi (argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT_NO);

    if(bind(sockfd , (struct sockaddr *) & serv_addr , sizeof(serv_addr))<0)
            error("Unable to bind");


    listen(sockfd , 4);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr , &clilen);

    if(newsockfd < 0 )
        error("Unable to accept");

    
    thread write_msg_thread(send_msg);
    thread read_msg_thread(receive_msg);
    
         write_msg_thread.join();

    this_thread::sleep_for(chrono::milliseconds(1000));

     if(read_msg_thread.joinable())
         read_msg_thread.join();
    

    close(newsockfd);
    close(sockfd);

    return 0;
    
}
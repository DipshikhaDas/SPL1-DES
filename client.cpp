#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<sstream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<thread>
#include<mutex>
#include"AES_Encryption.h"
#include"AES_Decryption.h"

using namespace std;

#define STRING_SIZE 1024
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 9999

int sockfd , portno , n;
char buffer[STRING_SIZE];

char read_buffer[STRING_SIZE], write_buffer[STRING_SIZE];

struct sockaddr_in serv_addr ;
struct hostent *server;


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
    FILE *file = fopen("enc_msg_c.txt","w");
    
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
        file = fopen("enc_msg_c.txt","r");
        fgets(write_buffer , STRING_SIZE , file);
        fclose(file);
         

        n = write(sockfd ,write_buffer, strlen(write_buffer));

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

        n = read(sockfd , read_buffer , STRING_SIZE);

        if(n<0)
            error("error in reaing");

        i = strncmp("Bye" , read_buffer , 3);

        if(i == 0)
            break;

        printf("[Server] : %s " , read_buffer);

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


int main(int argc , char *argv[])

{    
    portno = SERVER_PORT;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if(sockfd < 0)
    {
        error("Error in opening socket");

    } 

    server = gethostbyname(SERVER_ADDR);

    if(server == NULL)
        fprintf(stderr , " Error , no such host");

    bzero((char *) &serv_addr , sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *) server->h_addr_list[0] ,(char *) &serv_addr.sin_addr.s_addr , server->h_length);

    serv_addr.sin_port = htons(portno);

    if(connect(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr))<0)
        error("connection failed");

    
    thread write_msg_thread(send_msg);
    thread read_msg_thread(receive_msg);
    
         write_msg_thread.join();

    this_thread::sleep_for(chrono::milliseconds(1000));

    if(read_msg_thread.joinable())
         read_msg_thread.join();
    

    close(sockfd);
    return 0;
        
    }
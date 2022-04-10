#include<iostream>
#include<winsock.h>
using namespace std;

#define PORT 9901
struct sockaddr_in srv;
fd_set fr,fw,fe;
int nMaxFd;

int main()
{
    int nRet = 0;

    //initialize socket
    WSADATA ws;

    if(WSAStartup(MAKEWORD(2,2),&ws) < 0)
    {
        cout<<"not initialized"<<endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"initialized"<<endl;
    }

    int nSocket = socket (AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(nSocket<0)
    {
        cout<<"Not opened"<<endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"opened"<<endl<<nSocket<<endl;
    }


    //initialize environment for socket
    
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = INADDR_ANY;
    //srv.sin_addr.s_addr = in_addr("127.0.0.1");
    memset(&(srv.sin_zero),0,8);

    //Blocking and non blocking socket
    //optval = 0 means blocking and !=0 means not blocking

    // u_long optval = 0;

    // nRet = ioctlsocket(nSocket, FIONBIO, &optval);
     
    // if(nRet != 0)
    // {
    //     cout<<"ioctsocket call failed "<<endl;
    // }
    // else 
    // {
    //     cout<<"ioctsocket call passed  "<<endl;
    // } BY default blocking socket

    //setsock

    int nOptVal = 0;
    int nOptLen = sizeof(nOptVal);
    nRet = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nOptVal, nOptLen);
   
   if (!nRet)
   {
       cout<<"The setsocket call successfull "<<endl;
   }
   else
   {
       cout<<"setsocket call failed "<<endl;
       WSACleanup();
       exit(EXIT_FAILURE);
   }

   
    //Bind to local server

    nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));

    if(nRet<0)
    {
        cout<<"fail to bind"<<endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"Successfully bind to the local port"<<endl;
    }

    //Listen request from client(Queue of client request)

    nRet = listen(nSocket, 5);

    if(nRet < 0)
    {
        cout<<"Fail to listen to clients"<<endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"Started listen to client"<<endl;
    }


    nMaxFd = nSocket;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

   while(1)
   {  
        FD_ZERO(&fr);
        FD_ZERO(&fw);
        FD_ZERO(&fe);


        FD_SET(nSocket, &fr);
        FD_SET(nSocket, &fe);

        cout<<"Before select call : "<<fr.fd_count<<endl;

        //Keep waiting for new request and wait as per new request

        nRet = select(nMaxFd+1, &fr, &fw, &fe, &tv);

        if(nRet > 0)
        {
            //when someone connects with a message over a dedicated connection
        }
        else if(nRet == 0)
        {
            //none of the socket descriptor are ready
            cout<<"NOthing on port: "<<PORT<<endl;
        }
        else
        {
            //It failed
            cout<<"It failed "<<endl;
            exit(EXIT_FAILURE); 
        }

        cout<< "After select call : "<<fr.fd_count<<endl;
        Sleep(2000);  
   }

 }
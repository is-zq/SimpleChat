#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6666

using namespace std;

int main()
{
    int sock = socket(AF_INET ,SOCK_STREAM,0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.182.124");
    serv_addr.sin_port = htons(PORT);
    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));


    char message[40];

    read(sock,message,sizeof(message)-1);
    
    printf("Receive from server: %s\n",message);

    close(sock);

    return 0;


}

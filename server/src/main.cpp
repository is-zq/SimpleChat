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
    int listen_sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP) ;

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    
    bind(listen_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(listen_sock,100);

    while(1)
    {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);


        int clnt_sock = accept(listen_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
        char str[] ="Login Success";
        write(clnt_sock,str,sizeof(str));
        close(clnt_sock);
    }
    close(listen_sock);
}

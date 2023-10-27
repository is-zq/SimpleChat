#include "common.h"
#include "user_info.h"
#include "tcp_socket.h"

#define MAX_EVENTS 20

int main()
{
    TcpSocket listen_sock(htonl(INADDR_ANY),htons(PORT));
    std::cout<<"create sock"<<std::endl;
    if(!listen_sock.Listen())
    {
        perror("listen:");
        exit(-1);
    }
    std::cout<<"listening"<<std::endl;
    while(true)
    {
        TcpSocket client_sock = listen_sock.Accept();
        std::cout<<client_sock.get_sock()<<std::endl;
        std::string str = client_sock.Recv();
        std::cout<<str<<std::endl;
    }
}

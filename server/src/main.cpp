#include "common.h"
#include "user_info.h"
#include "tcp_socket.h"
#include <unordered_map>

#define MAX_EVENTS 20

int main()
{
    TcpSocket listen_sock(htonl(INADDR_ANY),htons(PORT));
    if(!listen_sock.Listen())
    {
        perror("listen:");
        exit(-1);
    }

    int epoll_fd = epoll_create(1);
    if(epoll_fd == -1)
    {
        perror("epoll_create:");
        exit(EXIT_FAILURE);
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock.get_sock();
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_sock.get_sock(),&ev) == -1)
    {
        perror("epoll_ctl:");
        exit(EXIT_FAILURE);
    }

    struct epoll_event events[MAX_EVENTS];
    std::unordered_map<int,TcpSocket> client_manager;
    while(true)
    {
        int num_events = epoll_wait(epoll_fd,events,1,-1);
        if(num_events == -1)
        {
            perror("epoll_wait:");
            exit(EXIT_FAILURE);
        }
        for(int i=0;i<num_events;i++)
        {
            if(events[i].data.fd == listen_sock.get_sock())
            {
                TcpSocket client_sock = listen_sock.Accept();
                ev.events = EPOLLIN;
                ev.data.fd = client_sock.get_sock();
                client_manager.emplace(client_sock.get_sock(),client_sock);
                if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_sock.get_sock(),&ev) == -1)
                {
                    perror("epoll_ctl:");
                }
            }
            else
            {
                TcpSocket &client_sock = client_manager[events[i].data.fd];
                std::string buf = client_sock.Recv();
                if(buf.size() == 0)
                {
                    struct in_addr addr;
                    addr.s_addr = client_sock.get_addr();
                    std::cout<<inet_ntoa(addr)<<"disconnected"<<std::endl;
                    client_manager.erase(client_manager.find(events[i].data.fd));
                }
                else
                {
                    std::cout<<buf<<std::endl;
                }
            }
        }
    }

    return 0;
}

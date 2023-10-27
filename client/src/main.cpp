#include "common.h"
#include "tcp_socket.h"

using namespace std;

int main(int argc,char *argv[])
{
    TcpSocket sock;
    if(!sock.Connect(inet_addr("192.168.182.124"),htons(PORT)))
    {
        perror("connect:");
        exit(-1);
    }
    sock.Send("Hello Socket!\n");

    return 0;
}

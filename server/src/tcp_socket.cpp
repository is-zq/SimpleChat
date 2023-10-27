#include "common.h"
#include "tcp_socket.h"

TcpSocket::TcpSocket()
{
    sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(sock == -1)
    {
        perror("create sock");
        exit(-1);
    }
}

TcpSocket::TcpSocket(int sock,long addr,int port)
{
    this->sock = sock;
    this->addr = addr;
    this->port = port;
}

TcpSocket::TcpSocket(long addr,int port)
{
    this->sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(this->sock == -1)
    {
        perror("create sock");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = addr;
    serv_addr.sin_port = port;
    if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    this->addr = addr;
    this->port = port;
}

TcpSocket::TcpSocket(TcpSocket&& other)
{
    this->sock = other.sock;
    this->addr = other.addr;
    this->port = other.port;
    other.sock = -1;
}

int TcpSocket::get_sock()
{
    return this->sock;
}

long TcpSocket::get_addr()
{
    return this->addr;
}

int TcpSocket::get_port()
{
    return this->port;
}

int TcpSocket::Listen()
{
    int ret = listen(this->sock,MAX_QUEUE);
    if(ret == 0)
        return 1;
    else
        return 0;
}

TcpSocket TcpSocket::Accept()
{
    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    if((clnt_sock = accept(this->sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size)) == -1)
    {
        perror("accepet");
        exit(-1);
    }
    return std::move(TcpSocket(clnt_sock,clnt_addr.sin_addr.s_addr,clnt_addr.sin_port));
}

int TcpSocket::Connect(long addr,int port)
{
    struct sockaddr_in op_addr;
    memset(&op_addr,0,sizeof(op_addr));
    op_addr.sin_family = AF_INET;
    op_addr.sin_addr.s_addr = addr;
    op_addr.sin_port = port;
    int ret = connect(this->sock,(struct sockaddr*)&op_addr,sizeof(op_addr));
    if(ret == 0)
        return 1;
    else
        return 0;
}

std::string TcpSocket::Recv()
{
    char buf[BUF_LEN] = {0};
    if(recv(this->sock,buf,BUF_LEN,0) == -1)
        return std::string();
    return std::string(buf);
}

int TcpSocket::Send(const std::string &msg)
{
    return send(this->sock,msg.c_str(),msg.size(),0);
}

TcpSocket::~TcpSocket()
{
    if(this->sock != -1)
    {
        close(this->sock);
    }
}

#ifndef _TCP_SOCKET_
#define _TCP_SOCKET_

#define BUF_LEN 1024

class TcpSocket
{
private:
    int sock;
    long addr;
    int port;

public:
    TcpSocket();                               //创建socket不绑定
    TcpSocket(int sock,long addr,int port);    //封装已有socket
    TcpSocket(long addr,int port);             //创建新的socket并绑定
    TcpSocket(TcpSocket&& other);                 //移动构造
    int get_sock();
    long get_addr();
    int get_port();
    TcpSocket Accept();
    int Connect(long addr,int port);
    std::string Recv();
    int Send(const std::string &msg);
    ~TcpSocket();
};

#endif

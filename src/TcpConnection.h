#pragma once

#include <list>
namespace libkafka{
  class TcpConnection{
  public:
    TcpConnection(const char* ip, short int port);
    ~TcpConnection();
    int connect();
    int send(const char* data, int len);
    int recv(char* buff, int len);

    int setRecvTimeout(int sec);

    private:
    const char* ip_;
    short int port_;
    int fd_;
  };

  class TcpConnectionPool{
    public:
    TcpConnectionPool(int max);
    ~TcpConnectionPool();
    TcpConnection* getConnection();
    void returnConnection(TcpConnection* conn);
    private:
    std::list<TcpConnection*> pool_;
    int max_;
  };
}

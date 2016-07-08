#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable> 

namespace libkafka{
  class TcpConnection{
  public:
    TcpConnection(const char* ip, short int port);
    ~TcpConnection();
    int connect();
    int send(const char* data, int len);
    int recv(char* buff, int len);

    int setRecvTimeout(int sec);

    int setSendTimeout(int sec);

    int keepalive();

    int nodelay();

    private:
    const char* ip_;
    short int port_;
    int fd_;
  };

  class TcpConnectionPool{
    public:
    TcpConnectionPool(int max, const char* ip, short int port);
    ~TcpConnectionPool();
    TcpConnection* getConnection();
    void returnConnection(TcpConnection* conn);
    private:
    std::list<TcpConnection*> pool_;
    int max_;
    const char* ip_;
    short int port_;
    int count_;
    std::mutex mutex_;
    std::condition_variable cond_;
  };
}

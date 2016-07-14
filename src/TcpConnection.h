#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string>

namespace libkafka{
  class TcpConnection{
  public:
    TcpConnection(std::string const& ip, short int port);
    ~TcpConnection();
    int connect();
    int send(const char* data, int len);
    int recv(char* buff, int len);

    int setRecvTimeout(int sec);

    int setSendTimeout(int sec);

    int keepalive();

    int nodelay();

  private:
    std::string ip_;
    short int port_;
    int fd_;
  };

  class TcpConnectionPool{
  public:
    TcpConnectionPool(int max, std::string const& ip, short int port);
    ~TcpConnectionPool();
    TcpConnection* getConnection();
    void returnConnection(TcpConnection* conn);
  private:
    std::list<TcpConnection*> pool_;
    int max_;
    std::string ip_;
    short int port_;
    int count_;
    std::mutex mutex_;
    std::condition_variable cond_;
  };

  class TcpConnectionGuard{
    public:
    TcpConnectionGuard(TcpConnectionPool* pool, TcpConnection* conn):
      pool_(pool),
      conn_(conn)
    {}
    ~TcpConnectionGuard(){
      if(pool_)
	pool_->returnConnection(conn_);
    }
    private:
    TcpConnectionGuard(const TcpConnectionGuard& other);
    TcpConnectionGuard& operator=(const TcpConnectionGuard& other);
    TcpConnectionPool* pool_;
    TcpConnection* conn_;
  };
}















#include "TcpConnection.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <strings.h>
#include <iostream>


namespace libkafka{
  TcpConnection::TcpConnection(std::string const& ip, short int port):
    ip_(ip),
    port_(port),
    fd_(-1){
    
  }
  
  TcpConnection::~TcpConnection(){
    if(fd_ >= 0){
      ::close(fd_);
    }
  }
  
  int TcpConnection::connect(){
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ < 0){
      return -1;
    }
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    serv_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    
    int flag = fcntl(fd_, F_GETFL, 0);
    fcntl(fd_, F_SETFL, flag | O_NONBLOCK);
    int ret = 0;
    ret = ::connect(fd_, (struct sockaddr*)&serv_addr, sizeof serv_addr);
    if(ret != 0){
      if(errno != EINPROGRESS){
	return -1;
      }else{
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	fd_set set;
	fd_set rset;
	FD_ZERO(&set);
	FD_ZERO(&rset);
	FD_SET(fd_, &set);
	FD_SET(fd_, &rset);
	ret = ::select(fd_ + 1, &rset, &set, NULL, &timeout);
	switch(ret){
	case 0:
	  //timeout
	  {
	    return -1;
	  }
	  break;
	case -1:
	  {
	    return -1;
	  }
	  break;
	case 1:
	  {
	    if(FD_ISSET(fd_, &set)){
	      fcntl(fd_, F_SETFL, flag & ~O_NONBLOCK);
	      return 0;
	    }
	    else {
	      return -1;
	    }
	  }
	  break;
	default:
	  break;
	}
      }
    }
    return -1;
  }
  
  int TcpConnection::send(const char* data, int len){
    int flag = 0;
    int writted = ::send(fd_, data, len, flag);
    if(writted == -1){
      //handle error
      return -1;
    }
    return writted;
  }
  
  int TcpConnection::recv(char* buff, int want){
    int read = 0;
    int flag = 0;
    char* start = buff;
    while(read < want){
      int n = ::recv(fd_, start, want - read, flag);
      if(n == -1){
	//handle error
	break;
      }
      read += n;
      start += n;
    }
    return read;
  }

  int TcpConnection::setRecvTimeout(int sec){
    struct timeval timeout{sec, 0};
    if(::setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) == -1){
      //handle error
      //strerror(errno)
      return -1;
    }
    return 0;
  }

  int TcpConnection::setSendTimeout(int sec){
    struct timeval timeout{sec, 0};
    if(::setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof timeout) == -1){
      return -1;
    }
    return 0;
  }

  int TcpConnection::keepalive(){
    int flag = 1;
    if(::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, (void *)&flag, sizeof(flag)) < 0){
      return -1;
    }
    return 0;
  }

  int TcpConnection::nodelay(){
    int flag = 1;
    if(::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(flag)) < 0){
      return -1;
    }
    return 0;
  }


  TcpConnectionPool::TcpConnectionPool(int max, std::string const& ip, short int port):
    max_(max),
    ip_(ip),
    port_(port),
    count_(0){
    
  }
  
  TcpConnectionPool::~TcpConnectionPool(){
    std::lock_guard<std::mutex> lock(mutex_);
    for(auto it : pool_){
      delete it;
    }
    pool_.clear();
  }
  
  TcpConnection* TcpConnectionPool::getConnection(){
    std::unique_lock<std::mutex> lock(mutex_);
    if(pool_.empty()){
      if(count_ <= max_){
	TcpConnection* conn = new TcpConnection(ip_, port_);
	if(conn->connect() < 0){
	  delete conn;
	  return 0;
	}
	++count_;
	conn->keepalive();
	conn->nodelay();
	return conn;
      }else{
	cond_.wait(lock, [&]() -> bool {return !pool_.empty();});
	TcpConnection* conn = pool_.front();
	pool_.pop_front();   
	return conn;
      }  
    }
    TcpConnection* conn = pool_.front();
    pool_.pop_front();   
    return conn;
  }
  
  void TcpConnectionPool::returnConnection(TcpConnection* conn){
    std::lock_guard<std::mutex> lock(mutex_);
    pool_.push_front(conn);
    cond_.notify_one();
  }
}













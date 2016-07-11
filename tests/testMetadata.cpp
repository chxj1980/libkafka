#include "../src/TcpConnection.h"
#include "../src/metadata/MetadataRequest.h"
#include "../src/metadata/MetadataResponse.h"
#include "../src/Encoder.h"
#include "../src/Decoder.h"
#include <iostream>
#include <arpa/inet.h>

using namespace libkafka;

int main(int argc, char** argv){
  if (argc != 2){
    std::cout << "usage:" << argv[0] << " ip" << std::endl;
    return -1;
  }
  TcpConnectionPool pool(10, argv[1], 9092);
  
  char sendbuff[8092] = {0};
  char recvbuff[8092] = {0};
  Encoder ec(sendbuff, sizeof(sendbuff));
  MetadataRequest metareq(1);
  metareq.add("test");
  metareq.write(&ec);
  int sendsize = ec.size();
  TcpConnection* conn = pool.getConnection();
  if(conn == 0){
    std::cout << "get conn error" << std::endl;
    return -1;
  }
  conn->send(sendbuff, sendsize);
  int netValue = -1;
  int ret = conn->recv((char*)&netValue, sizeof(int));
  if(ret == -1){
    std::cout << "read error" << std::endl;
    pool.returnConnection(conn);
    return -1;
  }
  int recvBytes = ntohl(netValue);
  std::cout << "response size:" << recvBytes << std::endl;
  ret = conn->recv(recvbuff, recvBytes);
  if(ret == -1){
    std::cout << "read error" << std::endl;
    return -1;
  }
  Decoder dc(recvbuff, sizeof(recvbuff));
  MetadataResponse metares;
  metares.read(&dc);
  metares.dump();
  //std::cout << "size:" << ret << std::endl;
  //std::cout << "recv metaresponse:" << std::string(recvbuff, ret) << std::endl;
  pool.returnConnection(conn);
  return 0;
}











#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include "TcpConnection.h"
#include "Message.h"
#include "metadata/MetadataResponse.h"

namespace libkafka{

  class ConnNode{
    public:
    std::string ip;
    short port;
  };

  class BrokerLink{
    public:
    BrokerLink(Broker const& broker):
      id_(broker.nodeId_),
      pool_(10, broker.host_.c_str(), broker.port_){
    }
    
    int id_;
    TcpConnectionPool pool_;
    private:
    BrokerLink(const BrokerLink& other);
    BrokerLink& operator=(const BrokerLink& other);
  };

  typedef std::shared_ptr<BrokerLink> linkptr;
  
  class Client{
  public:
    Client(std::string const& brokerlist);
    ~Client();

    int load(const char* file);

    int getMetadata(std::string const& topic);
    
    BrokerLink* tryGetLeader(std::string const& topic, int partitionId);

    int produce(std::string const& topic, int partitionId, int correlationId,
		const char* key, int key_length,
		const char* msg, int msg_length,
		char* extern_buff, int buff_length);

    int produce(std::string const& topic, int partitionId, int correlationId, MessageSetPtr setPtr, char* extern_buff, int buff_length);

    int getPartitionNum(std::string const& topic);


  private:
    int getLeaderFromMetadata(const MetadataResponse& metaRes);

  private:
    std::mutex mutex_;
    std::vector<ConnNode> nodes_;

    std::map<std::string, std::map<int, linkptr> > leaders_;
  };
}



















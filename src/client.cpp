#include "client.h"
#include "Util.h"
#include "Errors.h"
#include "metadata/MetadataRequest.h"
#include "metadata/MetadataResponse.h"
#include "produce/ProduceRequest.h"
#include "produce/ProduceResponse.h"
#include "Encoder.h"
#include "Decoder.h"
#include <arpa/inet.h>
#include <iostream>

namespace libkafka{

  Client::Client(std::string const& brokerlist){
    std::vector<std::string> conn_strs;
    split(brokerlist, conn_strs, ",");
    for(auto& it: conn_strs){
      std::vector<std::string> conn_str;
      split(it, conn_str, ":");
      if(conn_str.size() == 2){
	ConnNode cnode;
	cnode.ip = conn_str[0];
	cnode.port = atoi(conn_str[1].c_str());
	nodes_.push_back(cnode);
      }
    }
  }
  
  Client::~Client(){
  }

  int Client::load(const char *file){
    return 0;
  }
  
  BrokerLink* Client::tryGetLeader(std::string const& topic, int partitionId){
    auto it = leaders_.find(topic);
    if(it != leaders_.end()){
      auto iit = it->second.find(partitionId);
      if(iit != it->second.end()){
        return iit->second.get();
      }
    }
    return 0;
  }

  int Client::produce(std::string const& topic, int partitionId, int correlationId,
		      const char* key, int key_length,
		      const char* msg, int msg_length,
		      char* extern_buff, int buff_length){
    int ret = 0;
    BrokerLink* leader_link = tryGetLeader(topic, partitionId);
    if(leader_link == 0){
      ret = getMetadata(topic);
      if (ret != 0){
	return ret;
      }
      leader_link = tryGetLeader(topic, partitionId);
    }
    if(leader_link){
      //produce
      char recvbuff[2048] = {0};
      MessagePtr messagePtr(new Message(key, key_length, msg, msg_length));
      MessageSetPtr setPtr(new MessageSet);
      setPtr->add(messagePtr);
      ProduceRequest req(correlationId);
      req.add(topic, partitionId, setPtr);
      Encoder ec(extern_buff, buff_length);
      req.write(&ec);
      int sendSize = ec.size();
      TcpConnection* conn = leader_link->pool_.getConnection();
      TcpConnectionGuard guard(&(leader_link->pool_), conn);
      if(conn == 0){
	return CONNECT_FAILED;
      }
      ret = conn->send(extern_buff, sendSize);
      if(ret == -1){
	return SEND_FAILED;
      }
      int netValue = -1;
      ret = conn->recv((char*)&netValue, sizeof(int));
      if(ret == -1){
	return RECV_FAILED;
      }
      int recvBytes = ntohl(netValue);
      ret = conn->recv(recvbuff, recvBytes);
      if(ret == -1){
	return RECV_FAILED;
      }
      Decoder dc(recvbuff, recvBytes);
      ProduceResponse res;
      res.read(&dc);
      return res.check(topic, partitionId);
    }
    return LeaderNotAvailable;
  }


  int Client::getPartitionNum(std::string const& topic){
    return 0;
  }


  int Client::getMetadata(std::string const& topic){
    TcpConnection conn(nodes_[0].ip.c_str(), nodes_[0].port);
    if(conn.connect() < 0){
      return CONNECT_FAILED;
    }
    conn.nodelay();
    char sendbuff[1024] = {0};
    char recvbuff[2048] = {0};
    Encoder ec(sendbuff, sizeof(sendbuff));
    MetadataRequest metaReq(1);
    metaReq.add(topic);
    metaReq.write(&ec);
    int sendsize = ec.size();
    int ret = conn.send(sendbuff, sendsize);
    if(ret == -1){
      return SEND_FAILED;
    }
    int netValue = -1;
    ret = conn.recv((char*)&netValue, sizeof(int));
    if(ret == -1){
      return RECV_FAILED;
    }
    int recvBytes = ntohl(netValue);
    ret = conn.recv(recvbuff, recvBytes);
    if(ret == -1){
      return RECV_FAILED;
    }
    Decoder dc(recvbuff, sizeof(recvbuff));
    MetadataResponse metaRes;
    metaRes.read(&dc);
    ret = getLeaderFromMetadata(metaRes);
    return ret;
  }

  int Client::getLeaderFromMetadata(const MetadataResponse& metaRes){
    std::map<int, linkptr> links;
    for(auto const& it : metaRes.brokers_){
      links[it.nodeId_] = linkptr(new BrokerLink(it));
    }
    for(auto const& topic : metaRes.metadata_){
      if(topic.topicErrorCode_ != 0){
	return topic.topicErrorCode_;
      }
      for(auto const& partition : topic.partitionMetas_){
	if(partition.partitionErrorCode_ != 0){
	  continue;
	}
	leaders_[topic.topicName_][partition.partitionId_] = links[partition.leader_];
      }
    }
    return 0;
  }

}
















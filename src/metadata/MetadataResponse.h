#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../Response.h"

namespace libkafka{
  class Broker{
  public:
    int read(Decoder* dc);
    
    int nodeId_;
    std::string host_;
    int port_;
  };

  class PartitionMetadata{
  public:
    int read(Decoder* dc);
    
    short partitionErrorCode_;
    int partitionId_;
    int leader_;
    std::vector<int> replicas_;
    std::vector<int> isr_;
  };
  
  class TopicMetadata{
  public:
    int read(Decoder* dc);
    
    short topicErrorCode_;
    std::string topicName_;
    std::vector<PartitionMetadata> partitionMetas_;
  };

  class MetadataResponse : public Response{
  public:

    virtual int read(Decoder* dc);

    void dump();
   
    std::vector<Broker> brokers_;
    std::vector<TopicMetadata> metadata_;
  };
  
}

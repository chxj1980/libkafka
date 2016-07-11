#include "MetadataResponse.h"
#include "../Decoder.h"

namespace libkafka{

  int Broker::read(Decoder* dc){
    nodeId_ = dc->readInt32();
    host_ = dc->readString();
    port_ = dc->readInt32();
    return 0;
  }

  int PartitionMetadata::read(Decoder* dc){
    partitionErrorCode_ = dc->readInt16();
    partitionId_ = dc->readInt32();
    leader_ = dc->readInt32();
    int replicaSize = dc->readInt32();
    for(int i = 0; i < replicaSize; ++i){
      replicas_.push_back(dc->readInt32());
    }
    int isrSize = dc->readInt32();
    for(int i = 0; i < isrSize; ++i){
      isr_.push_back(dc->readInt32());
    }
    return 0;
  }

  int TopicMetadata::read(Decoder* dc){
    topicErrorCode_ = dc->readInt16();
    topicName_ = dc->readString();
    int metaSize = dc->readInt32();
    for(int i = 0; i < metaSize; ++i){
      PartitionMetadata pmeta;
      pmeta.read(dc);
      partitionMetas_.push_back(pmeta);
    }
    return 0;
  }

  int MetadataResponse::read(Decoder* dc){
    int correlationId = dc->readInt32();
    int brokerSize = dc->readInt32();
    for(int i = 0; i < brokerSize; ++i){
      Broker broker;
      broker.read(dc);
      brokers_.push_back(broker);
    }
    int metaSize = dc->readInt32();
    for(int i = 0; i < metaSize; ++i){
      TopicMetadata tmeta;
      tmeta.read(dc);
      metadata_.push_back(tmeta);
    }
    return 0;
  }

  void MetadataResponse::dump(){
    for(auto& it: brokers_){
      std::cout << "broker's id:" << it.nodeId_ << ", host:" << it.host_ << ", port:"<< it.port_ << std::endl; 
    }

    for(auto& it: metadata_){
      std::cout << "metadata: topic, topicErrorCode:" << it.topicErrorCode_ << ", topicName:" << it.topicName_ << std::endl;
      for(auto& iit : it.partitionMetas_){
	std::cout << "metadata: partition, partitionErrorCode:" << iit.partitionErrorCode_ <<
	  ", partitionId:" << iit.partitionId_ << ", leader:" << iit.leader_ << std::endl;
	for(auto& iiit : iit.replicas_){
	  std::cout << "replica id:" << iiit << std::endl;
	}
	for(auto& iiit : iit.isr_){
	  std::cout << "isr id:" << iiit << std::endl;
	}
      }
    }
  }
}











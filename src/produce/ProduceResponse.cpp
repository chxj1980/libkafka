#include "ProduceResponse.h"
#include "../Decoder.h"

namespace libkafka{
  ProduceResponse::ProduceResponse(){}
  ProduceResponse::~ProduceResponse(){}

  int ProduceResponse::read(Decoder* dc){
    int correlationId = dc->readInt32();
    //check
    int topicLength = dc->readInt32();
    for(int i = 0; i < topicLength; ++i){
      std::string topicName = dc->readString();
      int partitionLength = dc->readInt32();
      for(int j = 0; j < partitionLength; ++j){
	int partitionId = dc->readInt32();
	ProduceResponseState state;
	state.error_ = dc->readInt16();
	state.offset_ = dc->readInt64();
	responses_[topicName][partitionId] = state;
      }
    }
    return 0;
  }

  short ProduceResponse::check(const std::string &topic, int partitionId){
    auto it = responses_.find(topic);
    if(it == responses_.end()){
      return -1;
    }
    auto iit = it->second.find(partitionId);
    if(iit == it->second.end()){
      return -1;
    }
    return iit->second.error_;
  }
}

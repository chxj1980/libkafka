#include "MetadataRequest.h"
#include "../Encoder.h"

namespace libkafka{
  MetadataRequest::MetadataRequest(int correlationId):
    Request(correlationId){
    apiKey_ = 3;
  }

  MetadataRequest::~MetadataRequest(){}

  int MetadataRequest::write(Encoder* ec){
    ec->writeInt16(apiKey_);
    ec->writeInt16(apiVersion_);
    ec->writeInt32(correlationId_);
    ec->writeString(clientId_);
    ec->writeInt32(topics_.size());
    for(auto& it: topics_){
      ec->writeString(it);
    }
    //encode MetaReq done. now prependsize
    ec->prependSize();
    return 0;
  }

  void MetadataRequest::add(std::string const& topic){
    topics_.push_back(topic);
  }
}


















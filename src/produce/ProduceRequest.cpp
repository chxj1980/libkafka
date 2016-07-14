#include "ProduceRequest.h"
#include "../Encoder.h"
#include "../CalcSize.h"

namespace libkafka{

  ProduceRequest::ProduceRequest(int correlationId):
    Request(correlationId){
    apiKey_ = 0;
    /*
      If it is 0 the server will not send any response (this is the only case where the server will not reply to a request).
      If it is 1, the server will wait the data is written to the local log before sending a response.
      If it is -1 the server will block until the message is committed by all in sync replicas before sending a response.
    */
    requiredAcks_ = 1;
    timeout_ = 5000;//milliseconds
  }

  ProduceRequest::~ProduceRequest(){}

  void ProduceRequest::add(std::string const& topic, int partitonId, MessageSetPtr messageSet){
    messages_[topic][partitonId] = messageSet;
  }

  int ProduceRequest::write(Encoder* ec){
    ec->writeInt16(apiKey_);
    ec->writeInt16(apiVersion_);
    ec->writeInt32(correlationId_);
    ec->writeString(clientId_);

    ec->writeInt16(requiredAcks_);
    ec->writeInt32(timeout_);
    ec->writeInt32(messages_.size());
    for(auto const& it : messages_){
      ec->writeString(it.first);//write topic name.
      ec->writeInt32(it.second.size());
      for(auto const& iit : it.second){
	ec->writeInt32(iit.first);//write partition.
	ec->writeInt32(iit.second->size());//write set size.
	iit.second->write(ec);//write set
      }
    }
    
    ec->prependSize();
    return 0;
  }

}














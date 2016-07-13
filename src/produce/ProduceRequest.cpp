#include "ProduceRequest.h"
#include "../Encoder.h"
#include "../CalcSize.h"

namespace libkafka{

  Message::Message(int crc, char magic, char attr,
		   char* key, int keyLen,
		   char* value, int valueLen):
    crc_(crc),
    magicByte_(magic),
    attributes_(attr),
    key_(key),
    keyLength_(keyLen),
    value_(value),
    valueLength_(valueLen){
  }

  int Message::size(){
    CalcSize cs;
    cs.writeInt32(crc_);
    cs.writeInt8(magicByte_);
    cs.writeInt8(attributes_);
    cs.writeBytes(key_, keyLength_);
    cs.writeBytes(value_, valueLength_);
    return cs.size();
  }

  int Message::write(Encoder* ec){
    return 0;
  }

  void MessageSet::add(MessagePtr message){
  }

  int MessageSet::write(Encoder* ec){
    return 0;
  }

  ProduceRequest::ProduceRequest(int correlationId):
    Request(correlationId){
    apiKey_ = 0;
  }

  ProduceRequest::~ProduceRequest(){}

  void ProduceRequest::add(std::string const& topic, int partitonId, MessageSetPtr messageSet){
    
  }

  int ProduceRequest::write(Encoder* ec){
    return 0;
  }

}








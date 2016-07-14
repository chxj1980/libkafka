#include "Message.h"
#include "Encoder.h"
#include "CalcSize.h"

namespace libkafka{
  Message::Message(int crc, char magic, char attr,
		   const char* key, int keyLen,
		   const char* value, int valueLen):
    crc_(crc),
    magicByte_(magic),
    attributes_(attr),
    key_(key),
    keyLength_(keyLen),
    value_(value),
    valueLength_(valueLen){
  }

  Message::Message(const char* key, int keyLen, const char* value, int valueLen):
    crc_(0),
    /*
      This is a version id used to allow backwards compatible evolution of the message binary format.
      The current value is 1.
    */
    magicByte_(1),
    /*
      This byte holds metadata attributes about the message.
      The lowest 3 bits contain the compression codec used for the message.
      The fourth lowest bit represents the timestamp type. 0 stands for CreateTime and 1 stands for LogAppendTime.
      The producer should always set this bit to 0. (since 0.10.0)
      All other bits should be set to 0.
    */
    attributes_(0),
    key_(key),
    keyLength_(keyLen),
    value_(value),
    valueLength_(valueLen){
    //TODO  count crc
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
    ec->writeInt32(crc_);
    ec->beginCrc();
    ec->writeInt8(magicByte_);
    ec->writeInt8(attributes_);
    ec->writeBytes(key_, keyLength_);
    ec->writeBytes(value_, valueLength_);
    ec->endCrc();
    return 0;
  }

  void MessageSet::add(MessagePtr message){
    set_.push_back(message);
  }

  int MessageSet::write(Encoder* ec){
    long offset = 0;
    for(auto const& it : set_){
      ec->writeInt64(offset);
      ec->writeInt32(it->size());
      it->write(ec);
    }
    return 0;
  }

  int MessageSet::size(){
    CalcSize cs;
    long offset = 0;
    for(auto const& it : set_){
      cs.writeInt64(offset);
      cs.writeInt32(it->size());
      cs.incr(it->size());
    }
    return cs.size();
  }
}

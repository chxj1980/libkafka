#pragma once

#include "../Request.h"
#include <map>
#include <vector>
#include <memory>

namespace libkafka{
  //v0
  class Message{
  public:
    int crc_;
    char magicByte_;
    char attributes_;
    char* key_;
    int keyLength_;
    char* value_;
    int valueLength_;
  private:
    Message(const Message& other);
    Message& operator=(const Message& other);
  };
  typedef std::shared_ptr<Message> MessagePtr;

  class MessageOffset{
  public:
    long offset_;
    int messageSize_;
    MessagePtr message_;
  };
  
  class MessageSet{
  public:
    std::vector<MessageOffset> set_;
  };
  
  typedef std::shared_ptr<MessageSet> MessageSetPtr;
  
  class ProduceRequest: public Request{
  public:
    ProduceRequest(int correlationId);
    ~ProduceRequest();

    virtual int write(Encoder* ec);

  private:
    short requiredAcks_;
    int timeout_;
    std::map<std::string, std::map<int, MessageSetPtr> > messages_;
  };
}







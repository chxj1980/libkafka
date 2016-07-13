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
    Message(int crc, char magic, char attr,
	    char* key, int keyLen,
	    char* value, int valueLen);
    
    int write(Encoder* ec);

    int size();
    
  private:
    Message(const Message& other);
    Message& operator=(const Message& other);
  };
  typedef std::shared_ptr<Message> MessagePtr;

  class MessageSet{
  public:
    std::vector<MessagePtr> set_;
    void add(MessagePtr message);
    int write(Encoder* ec);
  };
  
  typedef std::shared_ptr<MessageSet> MessageSetPtr;
  
  class ProduceRequest: public Request{
  public:
    ProduceRequest(int correlationId);
    ~ProduceRequest();

    void add(std::string const& topic, int partitonId, MessageSetPtr messageSet);

    virtual int write(Encoder* ec);

  private:
    short requiredAcks_;
    int timeout_;
    std::map<std::string, std::map<int, MessageSetPtr> > messages_;
  };
}












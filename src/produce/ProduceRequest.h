#pragma once

#include "../Request.h"
#include "../Message.h"
#include <map>

namespace libkafka{
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












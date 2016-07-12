#pragma once

#include <string>

namespace libkafka{
  class Encoder;
  class Request{
  public:
    Request(int correlationId);
    ~Request();

    virtual int write(Encoder* ec);
    
  protected:
    short apiKey_;
    short apiVersion_;
    int correlationId_;
    std::string clientId_;
  };
}











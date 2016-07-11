#pragma once

#include "../Request.h"

namespace libkafka{
  class ProduceRequest: public Request{
    public:
    ProduceRequest(int correlationId);
    ~ProduceRequest();

    virtual int write(Encoder* ec);

    private:
    
  };
}

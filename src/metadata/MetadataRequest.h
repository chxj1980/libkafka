#pragma once

#include "../Request.h"
#include <vector>

namespace libkafka{
  class MetadataRequest : public Request{
  public:
    MetadataRequest(int correlationId);
    ~MetadataRequest();

    virtual int write(Encoder* ec);

    void add(std::string const& topic);

  private:
    std::vector<std::string> topics_;
  };
}











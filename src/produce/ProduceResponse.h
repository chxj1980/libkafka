#pragma once

#include <map>
#include <string>
#include "../Response.h"


namespace libkafka{


  class ProduceResponseState{
  public:
    short error_;
    long offset_;
  };
  
  class ProduceResponse : public Response{
  public:
    ProduceResponse();
    ~ProduceResponse();

    int read(Decoder* dc);

    short check(std::string const& topic, int partitionId);
    
  private:
    std::map<std::string, std::map<int, ProduceResponseState> > responses_;
  };
}











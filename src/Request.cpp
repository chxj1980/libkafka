#include "Request.h"

namespace libkafka{
  Request::Request(int correlationId):
    apiKey_(0),
    apiVersion_(0),
    correlationId_(correlationId),
    clientId_("libkafka_vv"){
    
  }

  Request::~Request(){}

  int Request::write(Encoder *ec){
    return 0;
  }
}

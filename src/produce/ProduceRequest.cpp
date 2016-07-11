#include "ProduceRequest.h"
#include "../Encoder.h"

namespace libkafka{

  ProduceRequest::ProduceRequest(int correlationId):
    Request(correlationId){
    apiKey_ = 0;
  }

  ProduceRequest::~ProduceRequest(){}

  int ProduceRequest::write(Encoder* ec){
    return 0;
  }

}

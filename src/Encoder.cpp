#include "Encoder.h"

namespace libkafka{
  Encoder::Encoder(char* buff, int len):
    buff_(buff),
    total_(len),
    index_(0){
    
  }
  Encoder::~Encoder(){}

  int Encoder::writeInt8(char data){
    return 0;
  }

  int Encoder::writeInt16(short int data){
    return 0;
  }

  int Encoder::writeInt32(int data){
    return 0;
  }

  int Encoder::writeInt64(long int data){
    return 0;
  }

  int Encoder::writeString(std::string const& data){
    return 0;
  }

  int Encoder::writeBytes(const char* data, int len){
    return 0;
  }
}

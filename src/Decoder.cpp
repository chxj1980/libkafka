#include "Decoder.h"

namespace libkafka{
  Decoder::Decoder(char* buff, int len):
    buff_(buff),
    total_(len),
    index_(0){
    
  }
  Decoder::~Decoder(){}

  char Decoder::readInt8(){
    return 0;
  }

  short int Decoder::readInt16(){
    return 0;
  }

  int Decoder::readInt32(){
    return 0;
  }

  long int Decoder::readInt64(){
    return 0;
  }

  std::string Decoder::readString(){
    return std::string();
  }

  int Decoder::readBytes(char* buff, int len){
    return 0;
  }
}

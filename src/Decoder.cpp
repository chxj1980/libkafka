#include "Decoder.h"
#include "Util.h"
#include <arpa/inet.h>
#include <string.h>

namespace libkafka{
  Decoder::Decoder(char* buff, int len):
    buff_(buff),
    start_(buff_),
    total_(len){
    
  }
  Decoder::~Decoder(){}

  char Decoder::readInt8(){
    char data = *(char*)start_;
    start_ += sizeof(char);
    return data;
  }

  short Decoder::readInt16(){
    short data = *(short*)start_;
    start_ += sizeof(short);
    data = ntohs(data);
    return data;
  }

  int Decoder::readInt32(){
    int data = *(int*)start_;
    start_ += sizeof(int);
    data = ntohl(data);
    return data;
  }

  long Decoder::readInt64(){
    long data = *(long*)start_;
    start_ += sizeof(long);
    data = ntoh64(data);
    return data;
  }

  std::string Decoder::readString(){
    short length = readInt16();
    std::string data(start_, length);
    start_ += length;
    return data;
  }

  char* Decoder::readBytes(int len){
    char* data = start_;
    start_ += len;
    return data;
  }
}











#include "Encoder.h"
#include "Util.h"
#include <arpa/inet.h>
#include <string.h>

namespace libkafka{
  Encoder::Encoder(char* buff, int len):
    buff_(buff),
    start_(buff_ + 4),
    total_(len),
    crc_start_(buff_),
    crc_end_(crc_start_){
    
  }
  Encoder::~Encoder(){}

  int Encoder::writeInt8(char data){
    if(size() + sizeof(data) > total_){return -1;}
    memcpy(start_, &data, sizeof data);
    start_ += sizeof(data);
    return 0;
  }

  int Encoder::writeInt16(short data){
    if(size() + sizeof(data) > total_){return -1;}
    short trans = htons(data);
    memcpy(start_, &trans, sizeof(trans));
    start_ += sizeof(trans);
    return 0;
  }

  int Encoder::writeInt32(int data){
    if(size() + sizeof(data) > total_){return -1;}
    int trans = htonl(data);
    memcpy(start_, &trans, sizeof(trans));
    start_ += sizeof(trans);
    return 0;
  }

  int Encoder::writeInt64(long data){
    if(size() + sizeof(data) > total_){return -1;}
    long trans = hton64(data);
    memcpy(start_, &trans, sizeof(trans));
    start_ += sizeof(trans);
    return 0;
  }

  int Encoder::writeString(std::string const& data){
    short int len = data.length();
    if(writeInt16(len) < 0){return -1;}
    if(size() + len > total_){return -1;}
    memcpy(start_, data.c_str(), len);
    start_ += len;
    return 0;
  }

  int Encoder::writeBytes(const char* data, int len){
    if(writeInt32(len) < 0){return -1;}
    if(size() + len > total_){return -1;}
    memcpy(start_, data, len);
    start_ += len;
    return 0;
  }

  void Encoder::beginCrc(){
    crc_start_ = start_;
  }

  void Encoder::endCrc(){
    crc_end_ = start_;
    int len = crc_end_ - crc_start_;
    int crc = crc32((const unsigned char*)crc_start_, len);
    updateInt32(crc, crc_start_ - sizeof(int));
  }

  void Encoder::updateInt32(int data, char *addr){
  }

  void Encoder::prependSize(){
    int trans = htonl(size() - 4);
    memcpy(buff_, &trans, sizeof(trans));
  }
}

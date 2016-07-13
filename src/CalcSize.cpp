#include "CalcSize.h"

namespace libkafka{
  CalcSize::CalcSize():index_(0){}
  CalcSize::~CalcSize(){}

  void CalcSize::writeInt8(char data){
    index_ += sizeof(data);
  }

  void CalcSize::writeInt16(short data){
    index_ += sizeof(data);
  }

  void CalcSize::writeInt32(int data){
    index_ += sizeof(data);
  }

  void CalcSize::writeInt64(long data){
    index_ += sizeof(data);
  }

  void CalcSize::writeString(std::string const& data){
    short len = data.length();
    writeInt16(len);
    index_ += len;
  }

  void CalcSize::writeBytes(const char* data, int len){
    writeInt32(len);
    index_ += len;
  }

  void CalcSize::incr(int size){
    index_ += size;
  }

  int CalcSize::size(){
    return index_;
  }
}



















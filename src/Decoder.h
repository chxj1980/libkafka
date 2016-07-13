#pragma once

#include <string>

namespace libkafka{
  class Decoder
  {
  public:
    Decoder(char* buff, int len);
    ~Decoder();

    char readInt8();

    short readInt16();

    int readInt32();

    long readInt64();

    std::string readString();

    char* readBytes(int len);

    int available(){
      return (total_ - (start_ - buff_));
    }

    bool hasError(){
      return hasError_;
    }

    void disable(){
      start_ = buff_;
      start_ += total_;
      hasError_ = true;
    }

  private:
    char* buff_;
    char* start_;
    int total_;
    bool hasError_;
  };

}











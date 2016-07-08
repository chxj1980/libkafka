#pragma once

#include <string>

namespace libkafka{
  class Decoder
  {
  public:
    Decoder(char* buff, int len);
    ~Decoder();

    char readInt8();

    short int readInt16();

    int readInt32();

    long int readInt64();

    std::string readString();

    int readBytes(char* buff, int len);//return read length

    private:
    char* buff_;
    int total_;

    int index_;
  };

}











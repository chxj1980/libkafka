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

    private:
    char* buff_;
    char* start_;
    int total_;
  };

}











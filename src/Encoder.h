#pragma once

#include <string>

namespace libkafka{
  class Encoder
  {
  public:
    Encoder(char* buff, int len);
    ~Encoder();

    int writeInt8(char data);

    int writeInt16(short int data);

    int writeInt32(int data);

    int writeInt64(long int data);

    int writeString(std::string const& data);

    int writeBytes(const char* data, int len);

    private:
    char* buff_;
    int total_;
    int index_;
  };

}

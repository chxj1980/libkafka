#pragma once

#include <string>

namespace libkafka{
  class Encoder
  {
  public:
    Encoder(char* buff, int len);
    ~Encoder();

    int writeInt8(char data);

    int writeInt16(short data);

    int writeInt32(int data);

    int writeInt64(long data);

    int writeString(std::string const& data);

    int writeBytes(const char* data, int len);

    int size(){
      return start_ - buff_;
    }

    //only should be called when message encode done.
    void prependSize();
    
    
  private:
    char* buff_;
    char* start_;
    int total_;
  };

}





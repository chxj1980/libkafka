#pragma once
#include <string>

namespace libkafka{
  class CalcSize{
  public:
    CalcSize();
    ~CalcSize();
    void writeInt8(char data);

    void writeInt16(short data);

    void writeInt32(int data);

    void writeInt64(long data);

    void writeString(std::string const& data);

    void writeBytes(const char* data, int len);

    int size();
  private:
    int index_;
  };
}

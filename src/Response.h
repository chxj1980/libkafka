#pragma once



namespace libkafka{
  class Decoder;
  class Response{
  public:
    Response();
    ~Response();

    virtual int read(Decoder* dc);
  };
}

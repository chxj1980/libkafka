#pragma once



namespace libkafka{
  class Decoder;
  class Response{
  public:
    Response();
    virtual ~Response();

    virtual int read(Decoder* dc);
  };
}

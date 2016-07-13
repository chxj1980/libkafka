#include "../src/client.h"
#include <iostream>
#include <string.h>


using namespace libkafka;

int main(int argc, char** argv){
  std::string brokerlist("10.149.11.147:9092");
  const char* key = 0;
  int keyLength = 0;
  const char* msg = "hello, this's my new kafka client library.";
  int msgLength = strlen(msg);
  char buff[8092] = {0};
  Client c(brokerlist);
  c.produce("test", 0, key, keyLength, msg, msgLength, buff, sizeof(buff));
  return 0;
}











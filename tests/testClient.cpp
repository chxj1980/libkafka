#include "../src/client.h"
#include <iostream>


using namespace libkafka;

int main(int argc, char** argv){
  std::string brokerlist("10.149.11.147:9092");
  Client c(brokerlist);
  c.getMetadata("test");
  return 0;
}

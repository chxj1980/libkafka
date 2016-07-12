#include "../src/Util.h"
#include <iostream>

using namespace libkafka;

int main(int argc, char** argv){
  std::string brokerlist("127.0.0.1:9092,10.0.0.1:9092,10.110.112.64:9092");
  std::vector<std::string> conn_vec;
  split(brokerlist, conn_vec, ",");
  for(auto& it : conn_vec){
    std::cout << "conn:" << it << std::endl;
  }
  return 0;
}

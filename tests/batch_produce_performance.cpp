#include "../src/client.h"
#include <iostream>
#include <string.h>
#include <sys/time.h>


using namespace libkafka;

class TimerSpec{
  public:
  TimerSpec(){
    gettimeofday(&start_, NULL);
  }

  ~TimerSpec(){
    struct timeval end;
    gettimeofday(&end, NULL);
    std::cout << "cost time: "<< ((end.tv_sec - start_.tv_sec)*1000 + (end.tv_usec - start_.tv_usec)/1000) <<" ms" << std::endl; 
  }

  private:
  struct timeval start_;
};

int main(int argc, char** argv){
  std::string brokerlist("10.149.11.147:9092");
  const char* key = 0;
  int keyLength = 0;

  const char* msg = "hello, this's produce performance test msg , the end";
  int msgLength = strlen(msg);
  char buff[204800] = {0};
  Client c(brokerlist);
  
  {
    int error_count = 0;
    int ret = 0;
    int correlationId = 0;
    int partitionId = 0;
    TimerSpec spec;
    std::cout << "test started, per msg length:" << msgLength << std::endl;
    MessageSetPtr setPtr(new MessageSet);
    for(int i = 0; i < 1000; ++i){
      MessagePtr message(new Message(key, keyLength, msg, msgLength));
      setPtr->add(message);
    }
    ret = c.produce("test", partitionId, correlationId, setPtr, buff, sizeof(buff));
    if(ret != 0){
      ++error_count ;
    }
    ++correlationId;
    partitionId = (++partitionId) % 5;
    std::cout << "test end, error count:" << error_count << std::endl;
  }
  return 0;
}










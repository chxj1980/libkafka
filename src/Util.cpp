#include "Util.h"

namespace libkafka{
  
  uint64_t ntoh64(uint64_t input){
    uint64_t rval;
    uint8_t *data = (uint8_t *)&rval;
    data[0] = input >> 56;
    data[1] = input >> 48;
    data[2] = input >> 40;
    data[3] = input >> 32;
    data[4] = input >> 24;
    data[5] = input >> 16;
    data[6] = input >> 8;
    data[7] = input >> 0;
    return rval;
  }

  uint64_t hton64(uint64_t input){
    return ntoh64(input);
  }

  int split(std::string const& str, std::vector<std::string>& ret, std::string sep){
    if (str.empty()){
      return -1;
    }
    std::string tmp;
    std::string::size_type pos_begin = str.find_first_not_of(sep);
    std::string::size_type comma_pos = 0;
    while (pos_begin != std::string::npos){
      comma_pos = str.find(sep, pos_begin);
      if (comma_pos != std::string::npos){
	tmp = str.substr(pos_begin, comma_pos - pos_begin);
	pos_begin = comma_pos + sep.length();
      }else{
	tmp = str.substr(pos_begin);
	pos_begin = comma_pos;
      }if (!tmp.empty()){
	ret.push_back(tmp);
	tmp.clear();
      }
    }
    return 0;
  }
}

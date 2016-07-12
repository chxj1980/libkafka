#pragma once

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string>
#include <vector>

namespace libkafka{

  uint64_t ntoh64(uint64_t input);

  uint64_t hton64(uint64_t input);

  int split(std::string const& str, std::vector<std::string>& ret, std::string sep = ",");
}

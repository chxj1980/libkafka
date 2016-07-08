#pragma once

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

namespace libkafka{

  uint64_t ntoh64(uint64_t input);

  uint64_t hton64(uint64_t input);
}

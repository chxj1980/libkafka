set(produce_HEADERS
  ProduceRequest.h
  ProduceResponse.h
  )

install(FILES ${produce_HEADERS} DESTINATION include/libkafka/produce)

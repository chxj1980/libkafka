set(protocol_SRCS
  TcpConnection.cpp
  Encoder.cpp
  CalcSize.cpp
  Decoder.cpp
  Util.cpp
  Request.cpp
  Response.cpp
  metadata/MetadataRequest.cpp
  metadata/MetadataResponse.cpp
  produce/ProduceRequest.cpp
  client.cpp
  )

add_compile_options(-std=c++11)

add_library(kafka ${protocol_SRCS})
install(TARGETS kafka DESTINATION lib)
ADD_LIBRARY(kafka-0.1 SHARED ${protocol_SRCS})
install(TARGETS kafka-0.1 DESTINATION lib)

set(HEADERS
  TcpConnection.h
  Encoder.h
  Decoder.h
  Request.h
  Response.h
  metadata/MetadataRequest.h
  metadata/MetadataResponse.h
  )

install(FILES ${HEADERS} DESTINATION include/libkafka)

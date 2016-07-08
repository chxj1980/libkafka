set(protocol_SRCS
  TcpConnection.cpp
  Encoder.cpp
  Decoder.cpp
  Util.cpp
  )

add_compile_options(-std=c++11)

add_library(kafka ${protocol_SRCS})
install(TARGETS kafka DESTINATION lib)
ADD_LIBRARY(kafka-0.1 SHARED ${protocol_SRCS})
install(TARGETS kafka-0.1 DESTINATION lib)

set(HEADERS
  )

install(FILES ${HEADERS} DESTINATION include/libkafka)

set(meta_HEADERS
  MetadataRequest.h
  MetadataResponse.h
  )

install(FILES ${meta_HEADERS} DESTINATION include/libkafka/metadata)

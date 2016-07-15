add_compile_options(-std=c++11)
add_executable(testMeta testMetadata.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testMeta kafka)

#add_executable(testSplit testSplit.cpp)
#LINK_DIRECTORIES(../src)
#target_link_libraries(testSplit kafka)

#add_executable(testClient testClient.cpp)
#LINK_DIRECTORIES(../src)
#target_link_libraries(testClient kafka)

add_executable(testProduce testProduce.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testProduce kafka)

add_executable(produce_performance produce_performance.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(produce_performance kafka)

add_executable(batch_produce_performance batch_produce_performance.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(batch_produce_performance kafka)

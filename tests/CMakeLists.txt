add_compile_options(-std=c++11)
add_executable(testMeta testMetadata.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testMeta kafka)

add_executable(testSplit testSplit.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testSplit kafka)

add_executable(testClient testClient.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testClient kafka)

add_compile_options(-std=c++11)
add_executable(testMeta testMetadata.cpp)
LINK_DIRECTORIES(../src)
target_link_libraries(testMeta kafka)

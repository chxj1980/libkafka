add_compile_options(-std=c++11)

add_executable(produce_example produce.cpp)
target_link_libraries(produce_example kafka)

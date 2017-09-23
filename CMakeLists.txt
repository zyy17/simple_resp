cmake_minimum_required(VERSION 3.7)
project(simple_resp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-ggdb3)
add_compile_options(-Wall)

include_directories(include)

set(SOURCE_FILES src/simple_resp.cc include/simple_resp.h)
add_library(simpleresp STATIC ${SOURCE_FILES})

add_executable(decode_test example/decode_test.cc)
target_link_libraries(decode_test simpleresp)

add_executable(encode_test example/encode_test.cc)
target_link_libraries(encode_test simpleresp)
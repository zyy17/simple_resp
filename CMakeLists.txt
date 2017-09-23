cmake_minimum_required(VERSION 3.7)
project(simple_resp)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_compile_options(-ggdb3)
add_compile_options(-Wall)

include_directories(include)

set(SOURCE_FILES src/simple_resp.cc include/simple_resp.h)
add_library(simpleresp STATIC ${SOURCE_FILES})

add_executable(basic_usage example/basic/basic_usage.cc)
target_link_libraries(basic_usage simpleresp)

add_executable(decode_encode_test test/decode_encode_test.cc)
target_link_libraries(decode_encode_test simpleresp)

add_test(decode_encode_test ./decode_encode_test)
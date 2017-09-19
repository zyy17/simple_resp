cmake_minimum_required(VERSION 3.7)
project(simple_resp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-ggdb3)
add_compile_options(-Wall)

include_directories(src)

set(SOURCE_FILES src/simple_resp.cpp src/simple_resp.h)
add_library(simpleresp STATIC ${SOURCE_FILES})

add_executable(decode_test example/decode_test.cpp)
target_link_libraries(decode_test simpleresp)
cmake_minimum_required(VERSION 3.19)
project(access)

set(CMAKE_CXX_STANDARD 11)

add_executable(access main.cpp)

target_include_directories(access PUBLIC include)
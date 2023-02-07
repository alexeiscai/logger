cmake_minimum_required(VERSION 3.10)
project(logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_library(logger SHARED src/logger.cpp)

add_executable(logApp main.cpp)
target_compile_features(logApp PRIVATE cxx_std_17)
target_link_libraries(logApp logger)

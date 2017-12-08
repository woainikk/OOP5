cmake_minimum_required(VERSION 3.8)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Factorization.cpp Factorization.h FileFactorise.cpp FileFactorise.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wl,--no-as-needed")
add_executable(Lab4 ${SOURCE_FILES})
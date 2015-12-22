cmake_minimum_required(VERSION 3.3)
project(SimulatedAnnealing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp KnapsackInstance.cpp KnapsackInstance.h KnapsackItem.cpp KnapsackItem.h KnapsackState.cpp KnapsackState.h config.h)
add_executable(SimulatedAnnealing ${SOURCE_FILES})
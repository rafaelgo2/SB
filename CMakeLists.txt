cmake_minimum_required(VERSION 3.6)
project(SB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES TP2/Montador/main.cpp TP2/Montador/Module.cpp)
add_executable(montador ${SOURCE_FILES})

set(SOURCE_FILES TP2/Linkador/main.cpp TP2/Linkador/Linker.cpp TP2/Linkador/ObjectModule.cpp)
add_executable(linkador ${SOURCE_FILES})

set(SOURCE_FILES TP2/Testador/main.cpp)
add_executable(testador ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.5)
project(APIManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c classes/APIManager/APIManager.c classes/APIManager/APIManager.h)
add_executable(APIManager ${SOURCE_FILES})
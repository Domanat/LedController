cmake_minimum_required(VERSION 3.15)

project(LEDCONTROLLER)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

#find_package(Boost 1.59 REQUIRED asio)
include_directories(${PROJECT_SOURCE_DIR}/libs/)

add_subdirectory(source)

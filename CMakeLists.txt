cmake_minimum_required(VERSION 3.10)
project(CacheLibrary)

set(CMAKE_CXX_STANDARD 17)

add_library(cache SHARED cache.cpp)
target_include_directories(cache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

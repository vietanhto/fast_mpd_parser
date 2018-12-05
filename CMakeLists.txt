cmake_minimum_required(VERSION 2.8.12)

project(fmp)

include_directories(include)

file(GLOB PROJECT_SRC src/fast_mpd_parser/*.cpp)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRC})
cmake_minimum_required(VERSION 2.8.12)

project(fast_mpd_parser)

include_directories(include)

file(GLOB PROJECT_SRC src/fast_mpd_parser/*.cpp src/main.cpp)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
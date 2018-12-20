cmake_minimum_required(VERSION 2.8.12)

project(fmp)

include_directories(include)

file(GLOB PROJECT_SRC src/fast_mpd_parser/*.cpp)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(${PROJECT_NAME} STATIC ${PROJECT_SRC})
add_executable(${PROJECT_NAME}_test tst/fast_mpd_parser/test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
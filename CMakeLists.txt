
project(randan)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
  
message(STATUS "Testing random number facilities")

include_directories("${PROJECT_BINARY_DIR}")

set (RANDAN_SOURCES
  main.cpp
  mt19937/mt19937.cpp
  rand/rand.c
  rand48/rand48.c
  random/random.c
  )

add_executable(randan ${RANDAN_SOURCES})
target_compile_options(randan PRIVATE
   $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
   $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -g -ggdb>
)

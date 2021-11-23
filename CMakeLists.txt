
project(randan)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
  
message(STATUS "Testing random number facilities")

include_directories("${PROJECT_BINARY_DIR}")

add_executable(randan main.cpp)
target_compile_options(randan PRIVATE
   $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
   $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -g -ggdb>
)

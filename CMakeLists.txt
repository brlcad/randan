
project(randan)
set(VERSION 1.0.0)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
  
message(STATUS "Testing random number facilities")

include_directories("${PROJECT_BINARY_DIR}")


set (RANDAN_SOURCES
  brlcad/bn_rand.c
  brlcad/bn_randhalf.c
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

if (NOT BRLCAD_ROOT)
  set (BRLCAD_ROOT /usr/brlcad)
endif (NOT BRLCAD_ROOT)
find_library(BRLCAD_LIBRARIES bn PATHS ${BRLCAD_ROOT}/lib)
if (BRLCAD_LIBRARIES)
  message("Enabling BRL-CAD random numbers")
  set(BRLCAD_INCLUDE_DIRS
    ${BRLCAD_ROOT}/include
    ${BRLCAD_ROOT}/../include
  )
  target_include_directories(randan PUBLIC "${BRLCAD_INCLUDE_DIRS}")
  target_link_libraries(randan "${BRLCAD_LIBRARIES}")
endif (BRLCAD_LIBRARIES)

install(TARGETS randan)

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "randan")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "C.S. Morrison")
set(CPACK_PACKAGE_VENDOR "")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION /usr/local /usr/local/bin)
include(CPack)

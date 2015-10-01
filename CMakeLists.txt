project(MatVGL)
cmake_minimum_required(VERSION 2.8)

if(UNIX AND NOT APPLE)
  set(SPECIFIC_INCLUDE_DIRECTORIES
      ${CMAKE_SOURCE_DIR}/include/linux)
  set(LIB_NAME
      matvgl)
  set(LINK_LIBRARIES)

  set(SOURCE_FILES
      ${CMAKE_SOURCE_DIR}/src/MatVGLSDL2Engine.cpp)
  set(HEADER_FILES
      ${CMAKE_SOURCE_DIR}/include/MatVGLEngine.hpp
      ${CMAKE_SOURCE_DIR}/include/stdafx.h
      ${CMAKE_SOURCE_DIR}/include/linux/MatVGLSDL2Engine.hpp)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR
       CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_C_FLAGS "-Wall -g -O0 -ggdb")
      set(CMAKE_CXX_FLAGS "-Wall -g -O0 -ggdb -std=c++11")
    endif()
  endif()
endif()

message(STATUS "C FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CXX FLAGS: ${CMAKE_CXX_FLAGS}")

include_directories(
  ${SPECIFIC_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include)

add_library(${LIB_NAME} SHARED
            ${SOURCE_FILES}
            ${HEADER_FILES})

target_link_libraries(${LIB_NAME}
                      ${LINK_LIBRARIES})

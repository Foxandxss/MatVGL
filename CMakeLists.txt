project(MatVGL)
cmake_minimum_required(VERSION 2.8)

if(UNIX AND NOT APPLE)
  include(FindPkgConfig)
  find_package(GLEW REQUIRED)
  pkg_search_module(SDL2 REQUIRED sdl2)
  find_package(OpenGL REQUIRED)

  set(LINK_LIBRARIES
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES})

  set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR})

  set(LIBRARY_NAME matvgl)

  set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/posix/MatVGL_Engine.cpp)
  set(HDR_FILES
    ${CMAKE_SOURCE_DIR}/include/MatVGL_Engine.hpp
    ${CMAKE_SOURCE_DIR}/include/MatVGL_Setup.hpp)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_C_FLAGS "-g3 -Wall -O0")
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS "-g3 -Wall -O0 -std=c++11")
    endif()
  endif()
endif()

message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'")
message(STATUS "C flags are '${CMAKE_C_FLAGS}'")
message(STATUS "CXX flags are '${CMAKE_C_FLAGS}'")

include_directories(${INCLUDE_DIRECTORIES})

add_library(${LIBRARY_NAME} SHARED
  ${SRC_FILES}
  ${HDR_FILES})

target_link_libraries(${LIBRARY_NAME} ${LINK_LIBRARIES})

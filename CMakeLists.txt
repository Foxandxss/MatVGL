# MatVGL (Matium Gaming Library). Cross platform game engine.
# Copyright (C) 2015 Víctor Matía Rodríguez <vmatir@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

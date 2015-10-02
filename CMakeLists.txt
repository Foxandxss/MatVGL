# MatVGL gaming library. Cross platform library to create games.
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

project(MatVGL) # The project itself
cmake_minimum_required(VERSION 2.8) # The minimum CMAKE version.

# The common header files for all platforms.
set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/MatVGLEngine.hpp
    ${CMAKE_SOURCE_DIR}/include/stdafx.h)

if(UNIX AND NOT APPLE) # Check for GNU/Linux systems.
  # Find the required modules.
  find_package(GLEW REQUIRED)

  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)

  find_package(OpenGL REQUIRED)

  # Create the specific includes for GNU/Linux systems.
  set(SPECIFIC_INCLUDE_DIRECTORIES
      ${CMAKE_SOURCE_DIR}/include/linux
      ${GLEW_INCLUDE_DIRS}
      ${SDL2_INCLUDE_DIRS}
      ${OPENGL_INCLUDE_DIR})
  # Set the library name for GNU/Linux systems.
  set(LIB_NAME
      matvgl)
  # Set the linked libraries for GNU/Linux systems.
  set(LINK_LIBRARIES
      ${GLEW_LIBRARIES}
      ${SDL2_LIBRARIES}
      ${OPENGL_LIBRARIES})

  # Set the source and header files for Linux systems.
  set(SPECIFIC_SOURCE_FILES
      ${CMAKE_SOURCE_DIR}/src/MatVGLSDL2Engine.cpp)
  set(SPECIFIC_HEADER_FILES
      ${HEADER_FILES}
      ${CMAKE_SOURCE_DIR}/include/linux/MatVGLSDL2Engine.hpp)

  # Set the flags for build type and for compiler ID.
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR
       CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_C_FLAGS "-Wall -g3 -O0 -ggdb3")
      set(CMAKE_CXX_FLAGS "-Wall -g3 -O0 -ggdb3 -std=c++11")
    endif()
  endif()
endif()

# Now the common include directories.
include_directories(
  ${SPECIFIC_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include)

# The library itself.
add_library(${LIB_NAME} SHARED
            ${SPECIFIC_SOURCE_FILES}
            ${SPECIFIC_HEADER_FILES}
            ${HEADER_FILES})

# And the libraries to be linked.
target_link_libraries(${LIB_NAME}
                      ${LINK_LIBRARIES})

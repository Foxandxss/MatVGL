project(MatVGL) # The project itself
cmake_minimum_required(VERSION 2.8) # The minimum CMAKE version.

# The common header files for all platforms.
set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/MatVGLEngine.hpp
    ${CMAKE_SOURCE_DIR}/include/stdafx.h)

if(UNIX AND NOT APPLE) # Check for GNU/Linux systems.
  # Create the specific includes for GNU/Linux systems.
  set(SPECIFIC_INCLUDE_DIRECTORIES
      ${CMAKE_SOURCE_DIR}/include/linux)
  # Set the library name for GNU/Linux systems.
  set(LIB_NAME
      matvgl)
  # Set the linked libraries for GNU/Linux systems.
  set(LINK_LIBRARIES)

  # Set the source and header files for Linux systems.
  set(SOURCE_FILES
      ${CMAKE_SOURCE_DIR}/src/MatVGLSDL2Engine.cpp)
  set(HEADER_FILES
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
            ${SOURCE_FILES}
            ${HEADER_FILES})

# And the libraries to be linked.
target_link_libraries(${LIB_NAME}
                      ${LINK_LIBRARIES})

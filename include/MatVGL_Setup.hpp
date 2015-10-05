// MatVGL (Matium Gaming Library). Cross platform game engine.
// Copyright (C) 2015 Víctor Matía Rodríguez <vmatir@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//////////////////////////////////////////////////////////////////////////////
/// \file MatVGL_Setup.hpp
/// \brief Header file for the library setup.
///
/// Sets the library up for portability. This is the only file that should hold
/// precompiler defines, OS checks and specific includes for the OS.
//////////////////////////////////////////////////////////////////////////////

#ifndef MATVGL_SETUP_HPP
#define MATVGL_SETUP_HPP

// Look for POSIX systems.
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))

// The includes needed.
#include <cstdint>  ///< Standard integer sizes.
#include <sstream>  ///< String streams.
#include <syslog.h> ///< System logs.

#include <GL/glew.h> ///< GLEW utils.

#include <SDL2/SDL.h>        ///< The SDL2 wrapper.
#include <SDL2/SDL_opengl.h> ///< The SDL2 wrapper for OpenGL.

#include <GL/gl.h> ///< The OpenGL library.

// The typedefs.
typedef SDL_Window MatVGL_Window; ///< Change the window name for portability.
typedef SDL_GLContext
    MatVGL_Context; ///< Change the GL context for portability.
typedef SDL_Event
    MatVGL_Event; ///< Change the window event name for portability.

// Usings.
using Int16 = int16_t;   ///< Change the int16_t name for portability.
using Int32 = int32_t;   ///< Change the int32_t name for portability.
using UInt32 = uint32_t; ///< Change the uint32_t name for portability.

#endif // POSIX systems

#endif // MATVGL_SETUP_HPP

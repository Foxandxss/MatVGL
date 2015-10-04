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

#ifndef MATVGL_SETUP_HPP
#define MATVGL_SETUP_HPP

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))

// The includes needed.
#include <cstdint>
#include <sstream>
#include <syslog.h>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>

// The typedefs.
typedef SDL_Window MatVGL_Window;
typedef SDL_GLContext MatVGL_Context;
typedef SDL_Event MatVGL_Event;

// Usings.
using Int16 = int16_t;
using Int32 = int32_t;
using UInt32 = uint32_t;

#endif // POSIX systems

#endif // MATVGL_SETUP_HPP

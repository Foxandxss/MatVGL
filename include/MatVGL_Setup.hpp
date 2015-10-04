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

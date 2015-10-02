// MatVGL gaming library. Cross platform library to create games.
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

#include "MatVGLSDL2Engine.hpp"

MatVGL::Engine *MatVGL::createGameEngine() {

  // We create the pointer to the engine in a secure way.
  static MatVGL::SDL2Engine *s_gameEngine = nullptr;
  if (!s_gameEngine) {
    s_gameEngine = new MatVGL::SDL2Engine();
  }

  // And we return it.
  return s_gameEngine;
}

MatVGL::SDL2Engine::SDL2Engine() {
  // Set the default values of the variables.
  p_windowProperties.title = "MatVGL Window";
  p_windowProperties.x = 0;
  p_windowProperties.y = 0;
  p_windowProperties.width = 0;
  p_windowProperties.height = 0;

  p_bgColor.red = 255;
  p_bgColor.green = 255;
  p_bgColor.blue = 255;
  p_bgColor.alpha = 255;

  p_viewportProperties.x = 0;
  p_viewportProperties.y = 0;
  p_viewportProperties.width = 0;
  p_viewportProperties.height = 0;

  p_isStartingUp = false;
  p_isReadyForUse = false;
  p_isShuttingDown = false;

  this->_window = nullptr;
  this->_glContext = 0;
}

// Shut the engine down, if it hasn't been shut down, yet.
MatVGL::SDL2Engine::~SDL2Engine() { this->shutDown(); }

void MatVGL::SDL2Engine::startEngine() {
  // Inform that we are starting up.
  p_isStartingUp = true;

  // Initialize SDL Video module.
  SDL_Init(SDL_INIT_VIDEO);

  // Set the window position.
  this->setWindowPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  // Get the display size.
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  // And set the window's size to the display's size.
  this->setWindowSize(current.w, current.h);

  // Set the default SDL GL attributes.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create the SDL window.
  this->_window = SDL_CreateWindow(
      p_windowProperties.title, p_windowProperties.x, p_windowProperties.y,
      p_windowProperties.width, p_windowProperties.height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
  // Create the SDL context.
  this->_glContext = SDL_GL_CreateContext(this->_window);

  // Initialize GLEW.
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    abort(); // Until we error check properly.
  }

  // Activate VSync (might want to move this into a settings portion).
  SDL_GL_SetSwapInterval(1);

  // Clear the background of the window.
  glClearDepth(1.0f);
  glClearColor((float)p_bgColor.red / 255.0f, (float)p_bgColor.green / 255.0f,
               (float)p_bgColor.blue / 255.0f, (float)p_bgColor.alpha / 255.0f);
  glDepthRange(0.0f, 1.0f);

  // Adjust the viewport to the window.
  this->adjustViewport();

  // Inform that we have started up already.
  p_isStartingUp = false;
  p_isReadyForUse = true;
}

void MatVGL::SDL2Engine::startFrame() {
  // Clear the buffers so that the newly rendered buffer can be put in the
  // front.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void MatVGL::SDL2Engine::endFrame() {
  // Swap the window's buffers.
  SDL_GL_SwapWindow(this->_window);
}

void MatVGL::SDL2Engine::shutDown() {
  // Inform that we are shutting the engine down.
  p_isShuttingDown = true;
  p_isReadyForUse = false;

  // Destroy the GL context.
  if (_glContext) {
    SDL_GL_DeleteContext(this->_glContext);
  }

  // Destroy the SDL window.
  if (_window) {
    SDL_DestroyWindow(this->_window);
  }

  // Quit SDL2.
  SDL_Quit();

  // We finished shutting down.
  p_isShuttingDown = false;
}

bool MatVGL::SDL2Engine::sleepForFrameLimit(UInt32 maxFrameRate) {
  // This isn't finished, clearly.
  // Returning false so that there's never an FPS cap apart from VSync.
  return false;
}

// All of the setters work in the same way: they change the variable or
// variables if they are new, then updates the window if it's already open, when
// necessary.
void MatVGL::SDL2Engine::setWindowTitle(const char *title) {
  // Set the window title if it's actually new.
  if (title != p_windowProperties.title) {
    p_windowProperties.title = title;

    // Update the corresponding window property if the window is already open.
    if (this->_window) {
      SDL_SetWindowTitle(this->_window, p_windowProperties.title);
    }
  }
}

void MatVGL::SDL2Engine::setWindowPosition(UInt32 x, UInt32 y) {
  if (x != p_windowProperties.x || y != p_windowProperties.y) {
    p_windowProperties.x = x;
    p_windowProperties.y = y;

    if (this->_window) {
      SDL_SetWindowPosition(this->_window, p_windowProperties.x,
                            p_windowProperties.y);
    }
  }
}

void MatVGL::SDL2Engine::setWindowSize(UInt32 width, UInt32 height) {
  if (width != p_windowProperties.width ||
      height != p_windowProperties.height) {
    p_windowProperties.width = width;
    p_windowProperties.height = height;

    if (this->_window) {
      SDL_SetWindowSize(this->_window, p_windowProperties.width,
                        p_windowProperties.height);
    }
  }
}

void MatVGL::SDL2Engine::setBackgroundColor(Int16 red, Int16 green, Int16 blue,
                                            Int16 alpha) {
  if (red != p_bgColor.red || green != p_bgColor.green ||
      blue != p_bgColor.blue || alpha != p_bgColor.alpha) {
    p_bgColor.red = red;
    p_bgColor.green = green;
    p_bgColor.blue = blue;
    p_bgColor.alpha = alpha;

    glClearColor((float)p_bgColor.red / 255.0f, (float)p_bgColor.green / 255.0f,
                 (float)p_bgColor.blue / 255.0f,
                 (float)p_bgColor.alpha / 255.0f);
  }
}

void MatVGL::SDL2Engine::adjustViewport() {
  // This function simply gets the window size.
  SDL_GetWindowSize(this->_window, (Int32 *)&p_windowProperties.width,
                    (Int32 *)&p_windowProperties.height);

  // So as to then adjust the viewport to the whole screen.
  this->setViewportPosition(0, 0);
  this->setViewportSize(p_windowProperties.height, p_windowProperties.height);
}

void MatVGL::SDL2Engine::setViewportPosition(UInt32 x, UInt32 y) {
  if (x != p_viewportProperties.x || y != p_viewportProperties.y) {
    p_viewportProperties.x = x;
    p_viewportProperties.y = y;

    glViewport(p_viewportProperties.x, p_viewportProperties.y,
               p_viewportProperties.width, p_viewportProperties.height);
    glScissor(p_viewportProperties.x, p_viewportProperties.y,
              p_viewportProperties.width, p_viewportProperties.height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glFlush();
  }
}

void MatVGL::SDL2Engine::setViewportSize(UInt32 width, UInt32 height) {
  if (width != p_viewportProperties.width ||
      height != p_viewportProperties.height) {
    p_viewportProperties.width = width;
    p_viewportProperties.height = height;

    glViewport(p_viewportProperties.x, p_viewportProperties.y,
               p_viewportProperties.width, p_viewportProperties.height);
    glScissor(p_viewportProperties.x, p_viewportProperties.y,
              p_viewportProperties.width, p_viewportProperties.height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glFlush();
  }
}

// The getters simply return a variable.
bool MatVGL::SDL2Engine::isStartingUp() { return p_isStartingUp; }

bool MatVGL::SDL2Engine::isReadyForUse() { return p_isReadyForUse; }

bool MatVGL::SDL2Engine::isShuttingDown() { return p_isShuttingDown; }

bool MatVGL::SDL2Engine::hasTheUserXedOut() {
  // In this getter, though, we have to check for the SDL events, and get the
  // QUIT event.
  while (SDL_PollEvent(&_event) != 0) {
    if (_event.type == SDL_QUIT) {
      return true;
    }
    return false;
  }

  return false;
}

MatVGL::Engine::WindowProperties MatVGL::SDL2Engine::getWindowProperties() {
  return p_windowProperties;
}

MatVGL::Engine::BackgroundColor MatVGL::SDL2Engine::getWindowBackgroundColor() {
  return p_bgColor;
}

MatVGL::Engine::ViewportProperties MatVGL::SDL2Engine::getViewportProperties() {
  return p_viewportProperties;
}

const char *MatVGL::SDL2Engine::getWindowTitle() {
  return p_windowProperties.title;
}

UInt32 MatVGL::SDL2Engine::getWindowX() { return p_windowProperties.x; }

UInt32 MatVGL::SDL2Engine::getWindowY() { return p_windowProperties.y; }

UInt32 MatVGL::SDL2Engine::getWindowWidth() { return p_windowProperties.width; }

UInt32 MatVGL::SDL2Engine::getWindowHeight() {
  return p_windowProperties.height;
}

Int16 MatVGL::SDL2Engine::getBackgroundRed() { return p_bgColor.red; }

Int16 MatVGL::SDL2Engine::getBackgroundGreen() { return p_bgColor.green; }

Int16 MatVGL::SDL2Engine::getBackgroundBlue() { return p_bgColor.blue; }

Int16 MatVGL::SDL2Engine::getBackgroundAlpha() { return p_bgColor.alpha; }

UInt32 MatVGL::SDL2Engine::getViewportX() { return p_viewportProperties.x; }

UInt32 MatVGL::SDL2Engine::getViewportY() { return p_viewportProperties.y; }

UInt32 MatVGL::SDL2Engine::getViewportWidth() {
  return p_viewportProperties.width;
}

UInt32 MatVGL::SDL2Engine::getViewportHeight() {
  return p_viewportProperties.height;
}

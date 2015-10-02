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
  static MatVGL::SDL2Engine *s_gameEngine = nullptr;
  if (!s_gameEngine) {
    s_gameEngine = new MatVGL::SDL2Engine();
  }

  return s_gameEngine;
}

MatVGL::SDL2Engine::SDL2Engine() {
  p_bgColor.red = 255;
  p_bgColor.green = 255;
  p_bgColor.blue = 255;
  p_bgColor.alpha = 255;

  p_isStartingUp = false;
  p_isReadyForUse = false;
  p_isShuttingDown = false;

  p_viewportHeight = 0;
  p_viewportWidth = 0;

  this->_window = nullptr;
  this->_glContext = 0;

  this->_windowX = 0;
  this->_windowY = 0;
  this->_windowW = 0;
  this->_windowH = 0;
}

MatVGL::SDL2Engine::~SDL2Engine() { this->shutDown(); }

void MatVGL::SDL2Engine::startEngine() {
  SDL_Init(SDL_INIT_VIDEO);

  this->_windowX = SDL_WINDOWPOS_CENTERED;
  this->_windowY = SDL_WINDOWPOS_CENTERED;

  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  this->_windowW = current.w;
  this->_windowH = current.h;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

  this->_window = SDL_CreateWindow(
      "MatVGL window", this->_windowX, this->_windowY, this->_windowW,
      this->_windowH, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
  this->_glContext = SDL_GL_CreateContext(this->_window);

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    abort(); // Until we error check properly.
  }

  SDL_GL_SetSwapInterval(1);

  glClearDepth(1.0f);
  glClearColor((float)p_bgColor.red / 255.0f, (float)p_bgColor.green / 255.0f,
               (float)p_bgColor.blue / 255.0f, (float)p_bgColor.alpha / 255.0f);
  glDepthRange(0.0f, 1.0f);

  this->adjustViewport();
}

void MatVGL::SDL2Engine::startFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void MatVGL::SDL2Engine::endFrame() { SDL_GL_SwapWindow(_window); }

void MatVGL::SDL2Engine::shutDown() {
  p_isShuttingDown = true;

  if (_glContext) {
    SDL_GL_DeleteContext(_glContext);
  }

  if (_window) {
    SDL_DestroyWindow(_window);
  }

  SDL_Quit();
}

bool MatVGL::SDL2Engine::sleepForFrameLimit(UInt32 maxFrameRate) {
  return false;
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
  SDL_GetWindowSize(this->_window, (Int32 *)&this->_windowW,
                    (Int32 *)&this->_windowH);

  glViewport(0, 0, this->_windowW, this->_windowH);
  glScissor(0, 0, this->_windowW, this->_windowH);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glFlush();
}

bool MatVGL::SDL2Engine::isStartingUp() { return p_isStartingUp; }

bool MatVGL::SDL2Engine::isReadyForUse() { return p_isReadyForUse; }

bool MatVGL::SDL2Engine::isShuttingDown() { return p_isShuttingDown; }

UInt32 MatVGL::SDL2Engine::getViewportWidth() { return p_viewportWidth; }

UInt32 MatVGL::SDL2Engine::getViewportHeight() { return p_viewportHeight; }

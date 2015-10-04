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

#include "MatVGL_Engine.hpp"

void MatVGL::Engine::setWindowTitle(const char *title) {
  MatVGL::Engine::windowTitle = title;
  if (window) {
    SDL_SetWindowTitle(MatVGL::Engine::window, title);
  }
}

const char *MatVGL::Engine::getWindowTitle() {
  return MatVGL::Engine::windowTitle;
}

void MatVGL::Engine::setWindowPosition(UInt32 x, UInt32 y) {
  windowPosition.x = x;
  windowPosition.y = y;

  if (window) {
    SDL_SetWindowPosition(window, x, y);
  }
}

MatVGL::Engine::WindowPosition MatVGL::Engine::getWindowPosition() {
  return windowPosition;
}

void MatVGL::Engine::setWindowSize(UInt32 w, UInt32 h) {
  windowSize.w = w;
  windowSize.h = h;

  if (window) {
    SDL_SetWindowSize(window, w, h);
  }
}

MatVGL::Engine::WindowSize MatVGL::Engine::getWindowSize() {
  return windowSize;
}

void MatVGL::Engine::adjustWindow(UInt32 x, UInt32 y, UInt32 w, UInt32 h) {
  windowPosition.x = x;
  windowPosition.y = y;
  windowSize.w = w;
  windowSize.h = h;

  if (window) {
    SDL_SetWindowPosition(window, x, y);
    SDL_SetWindowSize(window, w, h);
  }
}

void MatVGL::Engine::setViewportPosition(UInt32 x, UInt32 y) {
  viewportPosition.x = x;
  viewportPosition.y = y;

  glViewport(x, y, viewportSize.w, viewportSize.h);
}

MatVGL::Engine::ViewportPosition MatVGL::Engine::getViewportPosition() {
  return viewportPosition;
}

void MatVGL::Engine::setViewportSize(UInt32 w, UInt32 h) {
  viewportSize.w = w;
  viewportSize.h = h;

  glViewport(viewportPosition.x, viewportPosition.y, w, h);
}

MatVGL::Engine::ViewportSize MatVGL::Engine::getViewportSize() {
  return viewportSize;
}

void MatVGL::Engine::adjustViewport() {
  SDL_GetWindowSize(window, (Int32 *)&windowSize.w, (Int32 *)&windowSize.h);
  viewportPosition.x = 0;
  viewportPosition.y = 0;
  viewportSize.w = windowSize.w;
  viewportSize.h = windowSize.h;

  glViewport(viewportPosition.x, viewportPosition.y, viewportSize.w,
             viewportSize.h);
}

void MatVGL::Engine::adjustViewport(UInt32 x, UInt32 y, UInt32 w, UInt32 h) {
  viewportPosition.x = x;
  viewportPosition.y = y;
  viewportSize.w = w;
  viewportSize.h = h;

  glViewport(viewportPosition.x, viewportPosition.y, viewportSize.w,
             viewportSize.h);
}

void MatVGL::Engine::setBackgroundColor(Int16 r, Int16 g, Int16 b, Int16 a) {
  bgColor.r = r;
  bgColor.g = g;
  bgColor.b = b;
  bgColor.a = a;

  glClearColor((float)r / 250.0f, (float)g / 250.0f, (float)b / 250.0f,
               (float)a / 250.0f);
}

bool MatVGL::Engine::getIsStarting() { return isStarting; }

bool MatVGL::Engine::getIsReadyForUse() { return isReadyForUse; }

bool MatVGL::Engine::getIsStopping() { return isStopping; }

bool MatVGL::Engine::getUserHasXedOut() {
  if (window) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        return true;
      }

      return false;
    }
  }

  return false;
}

void MatVGL::Engine::start() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw MatVGL::Engine::StartFailure(SDL_GetError());
  }

  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to set the GL context major version to 3: "
            << SDL_GetError())
            .str()
            .c_str());
  }
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to set the GL context minor version to 2: "
            << SDL_GetError())
            .str()
            .c_str());
  }
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                          SDL_GL_CONTEXT_PROFILE_CORE) < 0) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to set the GL context profile mask to core: "
            << SDL_GetError())
            .str()
            .c_str());
  }

  MatVGL::Engine::setWindowPosition(SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED);
  window = SDL_CreateWindow(windowTitle, windowPosition.x, windowPosition.y,
                            windowSize.w, windowSize.h,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!window) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(std::stringstream()
                                         << "Failed to create the SDL window: "
                                         << SDL_GetError())
            .str()
            .c_str());
  }
  SDL_GetWindowSize(window, (Int32 *)&windowSize.w, (Int32 *)&windowSize.h);

  context = SDL_GL_CreateContext(window);
  if (!context) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to create the SDL GL context: " << SDL_GetError())
            .str()
            .c_str());
  }

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(std::stringstream()
                                         << "Failed to initialize GLEW: "
                                         << glewGetErrorString(glewError))
            .str()
            .c_str());
  }

  glClearColor((float)bgColor.r / 250.0f, (float)bgColor.g / 250.0f,
               (float)bgColor.b / 250.0f, (float)bgColor.a / 250.0f);
  adjustViewport();
}

void MatVGL::Engine::stop() {
  if (context) {
    SDL_GL_DeleteContext(context);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

MatVGL::Engine::StartFailure::StartFailure() : extraInfo_("") {}

MatVGL::Engine::StartFailure::StartFailure(const char *extraInfo)
    : extraInfo_(extraInfo) {}

const char *MatVGL::Engine::StartFailure::what() const throw() {
  if (extraInfo_ && !extraInfo_[0]) {
    syslog(LOG_ERR, "%s", "Unable to initialize MatVGL");
    return "Exception thrown. Unable to initialize MatVGL";
  }

  std::stringstream ss;
  ss << "Exception thrown. Unable to initialize MatVGL. " << extraInfo_;
  syslog(LOG_ERR, "%s", ss.str().c_str());
  return ss.str().c_str();
}

void MatVGL::Engine::startFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MatVGL::Engine::endFrame() { SDL_GL_SwapWindow(window); }

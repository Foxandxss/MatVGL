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

// The setters work the same way, just each for their own variables.
void MatVGL::Engine::setWindowTitle(const char *title) {
  // We set the variable as asked.
  MatVGL::Engine::windowTitle = title;
  // Then we check if the window is open and, if it is, we update it.
  if (window) {
    SDL_SetWindowTitle(MatVGL::Engine::window, title);
  }
}

// The getters simply return the desired variable.
const char *MatVGL::Engine::getWindowTitle() {
  return MatVGL::Engine::windowTitle;
}

// Even if this one has two variables, the concept is the same.
void MatVGL::Engine::setWindowPosition(UInt32 x, UInt32 y) {
  windowPosition.x = x;
  windowPosition.y = y;

  if (window) {
    SDL_SetWindowPosition(window, x, y);
  }
}

// These special ones also return two variables at once, in the form of a
// struct. There's not really a getX position, it's just a getPosition.x or
// getPosition.y. The same applies for other structs being get.
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

// This one allows us to change both the positon and th size of the window at
// the same time.
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

// This one simply sets the viewport to start at (0, 0) and be of the same size
// as the window, adjusting it.
void MatVGL::Engine::adjustViewport() {
  SDL_GetWindowSize(window, (Int32 *)&windowSize.w, (Int32 *)&windowSize.h);
  viewportPosition.x = 0;
  viewportPosition.y = 0;
  viewportSize.w = windowSize.w;
  viewportSize.h = windowSize.h;

  glViewport(viewportPosition.x, viewportPosition.y, viewportSize.w,
             viewportSize.h);
}

// The overloaded counterpart to the adjustViewport() simply allows us to change
// both the position and the size at the same time.
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
  // We check if there is a window.
  if (window) {
    // If there is, we get the events that are being received.
    while (SDL_PollEvent(&event) != 0) {
      // If one of those events is the SDL_QUIT event.
      if (event.type == SDL_QUIT) {
        // We can say it's true we are quitting.
        return true;
      }

      // In any other case, we say it's false.
      return false;
    }
  }

  // There isn't a window, so we can assume this is false.
  return false;
}

void MatVGL::Engine::start() {
  // We first initialize the needed SDL modules, and throw an exception on
  // error. Note that the static_cast in these throws is allowing us to combine
  // several string literals and constants into a single one, which is what is
  // asked by the function, a single string.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to initialize the SDL modules: " << SDL_GetError())
            .str()
            .c_str());
  }

  // Now we set several GL attributes through SDL's functions, and throw
  // exceptions if there is an error. Note that these are meant to mark how the
  // engine will be coded, the version of OpenGL with the Core profile, hence
  // why they also throw a start failure exception, which means the engine
  // couldn't start properly, instead of a different exception that users could
  // ignore.
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

  // Now we can set the window in a centered position.
  MatVGL::Engine::setWindowPosition(SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED);
  // And create it. We don't need the size of the window, since it will be a
  // full screen desktop window, which adapts to the size of the screen.
  //
  // TODO: add the possibility to create different kind of windows, at least a
  // normal window (maximizable and not maximizable) and a real full screen
  // window
  window = SDL_CreateWindow(windowTitle, windowPosition.x, windowPosition.y,
                            windowSize.w, windowSize.h,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!window) { // If the window failed to be created, throw an exception.
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(std::stringstream()
                                         << "Failed to create the SDL window: "
                                         << SDL_GetError())
            .str()
            .c_str());
  }
  // Now that the window is full screen and created, we can set the size
  // variables in the struct to those of the window, so that the struct
  // information is real and correct. Note that SDL2 needs int (int32_t/Int32),
  // hence why it's being casted into it.
  SDL_GetWindowSize(window, (Int32 *)&windowSize.w, (Int32 *)&windowSize.h);

  // We can now create the SDL GL context for the window, also checking for
  // errors.
  context = SDL_GL_CreateContext(window);
  if (!context) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(
            std::stringstream()
            << "Failed to create the SDL GL context: " << SDL_GetError())
            .str()
            .c_str());
  }

  // After all of this, we will initialize GLEW, checking for possible errors to
  // throw.
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    throw MatVGL::Engine::StartFailure(
        static_cast<std::stringstream &>(std::stringstream()
                                         << "Failed to initialize GLEW: "
                                         << glewGetErrorString(glewError))
            .str()
            .c_str());
  }

  // With all initialize, we set the default background color.
  glClearColor((float)bgColor.r / 250.0f, (float)bgColor.g / 250.0f,
               (float)bgColor.b / 250.0f, (float)bgColor.a / 250.0f);
  // And we adjust the viewport to the window by default.
  MatVGL::Engine::adjustViewport();
}

void MatVGL::Engine::stop() {
  // This is a cleaning function, equivalent to a destructor in a class. We need
  // to destroy everything we've created and quit all of the SDL modules.
  if (context) {
    SDL_GL_DeleteContext(context);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

// In this constructor, we will be saying there's no extra information, since we
// aren't passing the string to it.
MatVGL::Engine::StartFailure::StartFailure() : extraInfo_("") {
  // In both constructors, we will be logging the throw. In POSIX systems we
  // will be using the syslog.
  syslog(LOG_ERR, "%s", "Unable to initialize MatVGL");
}

// In this other constructor, since there is extra information, we can set the
// private variable accordingly.
MatVGL::Engine::StartFailure::StartFailure(const char *extraInfo)
    : extraInfo_(extraInfo) {
  std::stringstream ss;
  ss << "Unable to initialize MatVGL: " << this->extraInfo_;
  syslog(LOG_ERR, "%s", ss.str().c_str());

  // We do the syslog in the constructors, because this will make the thrown
  // exception be put into the log even if the user didn't call for the "what()"
  // function of the exception class.
}

// In the what function, we will return the passed information.
const char *MatVGL::Engine::StartFailure::what() const throw() {
  // This return will happen when there's no extra information (or if the extra
  // information is "").
  if (extraInfo_ && !extraInfo_[0]) {
    return "Exception thrown. Unable to initialize MatVGL";
  }

  // While here, with a string stream, we will be able to return the rest of the
  // information.
  std::stringstream ss;
  ss << "Exception thrown. Unable to initialize MatVGL. " << extraInfo_;
  return ss.str().c_str();
}

void MatVGL::Engine::startFrame() {
  // We have to clear the buffers so that everything can be rendered onto them.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TODO: rendering.
}

void MatVGL::Engine::endFrame() {
  // TODO: frame capping, cleaning if needed...

  // We have to swap the buffers of the window so that the newly rendered items
  // can be displayed onto the screen.
  SDL_GL_SwapWindow(window);
}

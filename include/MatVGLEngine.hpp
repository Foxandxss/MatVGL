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

#ifndef MATVGLENGINE_HPP
#define MATVGLENGINE_HPP

#include "stdafx.h"

namespace MatVGL {
class Engine {
protected:
  struct BackgroundColor {
    Int16 red;
    Int16 green;
    Int16 blue;
    Int16 alpha;
  };

  struct WindowProperties {
    const char *title;
    UInt32 x;
    UInt32 y;
    UInt32 width;
    UInt32 height;
  };

  struct ViewportProperties {
    UInt32 x;
    UInt32 y;
    UInt32 width;
    UInt32 height;
  };

  BackgroundColor p_bgColor;
  WindowProperties p_windowProperties;
  ViewportProperties p_viewportProperties;

  bool p_isStartingUp;
  bool p_isReadyForUse;
  bool p_isShuttingDown;

public:
  virtual ~Engine() {}

  virtual void startEngine() = 0;
  virtual void startFrame() = 0;
  virtual void endFrame() = 0;
  virtual void shutDown() = 0;

  virtual bool sleepForFrameLimit(UInt32 maxFrameRate) = 0;

  virtual void setWindowTitle(const char *title) = 0;
  virtual void setWindowPosition(UInt32 x, UInt32 y) = 0;
  virtual void setWindowSize(UInt32 width, UInt32 height) = 0;
  virtual void setBackgroundColor(Int16 red, Int16 green, Int16 blue,
                                  Int16 alpha) = 0;
  virtual void adjustViewport() = 0;
  virtual void setViewportPosition(UInt32 x, UInt32 y) = 0;
  virtual void setViewportSize(UInt32 width, UInt32 height) = 0;

  virtual bool isStartingUp() = 0;
  virtual bool isReadyForUse() = 0;
  virtual bool isShuttingDown() = 0;
  virtual bool hasTheUserXedOut() = 0;

  virtual WindowProperties getWindowProperties() = 0;
  virtual BackgroundColor getWindowBackgroundColor() = 0;
  virtual ViewportProperties getViewportProperties() = 0;

  virtual const char *getWindowTitle() = 0;

  virtual UInt32 getWindowX() = 0;
  virtual UInt32 getWindowY() = 0;
  virtual UInt32 getWindowWidth() = 0;
  virtual UInt32 getWindowHeight() = 0;
  virtual Int16 getBackgroundRed() = 0;
  virtual Int16 getBackgroundGreen() = 0;
  virtual Int16 getBackgroundBlue() = 0;
  virtual Int16 getBackgroundAlpha() = 0;
  virtual UInt32 getViewportX() = 0;
  virtual UInt32 getViewportY() = 0;
  virtual UInt32 getViewportWidth() = 0;
  virtual UInt32 getViewportHeight() = 0;
};

Engine *createGameEngine();
}

#endif // MATVGLENGINE_HPP

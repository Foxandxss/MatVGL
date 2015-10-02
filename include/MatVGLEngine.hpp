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
public:
  virtual ~Engine() {}

  virtual void startEngine() = 0;
  virtual void startFrame() = 0;
  virtual void endFrame() = 0;
  virtual void shutDown() = 0;

  virtual bool sleepForFrameLimit(UInt32 maxFrameRate) = 0;

  virtual void setBackgroundColor(Int16 red, Int16 green, Int16 blue,
                                  Int16 alpha) = 0;
  virtual void adjustViewport() = 0;

  virtual bool isStartingUp() = 0;
  virtual bool isReadyForUse() = 0;
  virtual bool isShuttingDown() = 0;
  virtual UInt32 getViewportWidth() = 0;
  virtual UInt32 getViewportHeight() = 0;

private:
  struct BackgroundColor {
    Int16 red;
    Int16 green;
    Int16 blue;
    Int16 alpha;
  };

protected:
  BackgroundColor p_bgColor;
  bool p_isStartingUp;
  bool p_isReadyForUse;
  bool p_isShuttingDown;
  UInt32 p_viewportWidth;
  UInt32 p_viewportHeight;
};

Engine *createGameEngine();
}

#endif // MATVGLENGINE_HPP

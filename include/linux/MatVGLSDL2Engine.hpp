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

#ifndef MATVGLSDL2ENGINE_HPP
#define MATVGLSDL2ENGINE_HPP

#include "MatVGLEngine.hpp"
#include "stdafx.h"

#include <GL/gl.h>

namespace MatVGL {
class SDL2Engine : public Engine {
public:
  SDL2Engine();

  void startEngine();
  void startFrame();
  void endFrame();
  void shutDown();

  bool sleepForFrameLimit(UInt32 maxFrameRate);

  void setBackgroundColor(Int16 red, Int16 green, Int16 blue, Int16 alpha);

  bool isStartingUp();
  bool isReadyForUse();
  bool isShuttingDown();
  UInt32 getViewportWidth();
  UInt32 getViewportHeight();
};
}

#endif // MATVGLSDL2ENGINE_HPP

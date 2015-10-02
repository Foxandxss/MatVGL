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
}

void MatVGL::SDL2Engine::startEngine() {}

void MatVGL::SDL2Engine::startFrame() {}

void MatVGL::SDL2Engine::endFrame() {}

void MatVGL::SDL2Engine::shutDown() {}

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

bool MatVGL::SDL2Engine::isStartingUp() { return p_isStartingUp; }

bool MatVGL::SDL2Engine::isReadyForUse() { return p_isReadyForUse; }

bool MatVGL::SDL2Engine::isShuttingDown() { return p_isShuttingDown; }

UInt32 MatVGL::SDL2Engine::getViewportWidth() { return p_viewportWidth; }

UInt32 MatVGL::SDL2Engine::getViewportHeight() { return p_viewportHeight; }

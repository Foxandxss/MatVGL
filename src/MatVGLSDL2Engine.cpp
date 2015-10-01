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

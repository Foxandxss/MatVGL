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

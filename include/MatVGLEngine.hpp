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

  virtual bool isStartingUp() = 0;
  virtual bool isReadyForUse() = 0;
  virtual bool isShuttingDown() = 0;
  virtual Int32 getViewportWidth() = 0;
  virtual Int32 getViewportHeight() = 0;

private:
  struct BackgroundColor {
    Int16 red;
    Int16 green;
    Int16 blue;
    Int16 alpha;
  };

protected:
  BackgroundColor p_bgColor;
};
}

#endif // MATVGLENGINE_HPP

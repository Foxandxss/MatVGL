#ifndef MATVGL_ENGINE_HPP
#define MATVGL_ENGINE_HPP

#include "MatVGL_Setup.hpp"

namespace MatVGL {
namespace Engine {

// The variables needed.
MatVGL_Window *window = nullptr;
const char *windowTitle = "MatVGL Window";
MatVGL_Context context = 0;
MatVGL_Event event;

bool isStarting = false;
bool isReadyForUse = false;
bool isStopping = false;

struct WindowPosition {
    UInt32 x = 0;
    UInt32 y = 0;
} windowPosition;

struct WindowSize {
    UInt32 w = 0;
    UInt32 h = 0;
} windowSize;

struct ViewportPosition {
    UInt32 x = 0;
    UInt32 y = 0;
} viewportPosition;

struct ViewportSize {
    UInt32 w = 0;
    UInt32 h = 0;
} viewportSize;

struct BackgroundColor {
  Int16 r = 255;
  Int16 g = 255;
  Int16 b = 255;
  Int16 a = 255;
} bgColor;

// Setters and getters for the variables.
void setWindowTitle(const char *title);
const char *getWindowTitle();

void setWindowPosition(UInt32 x, UInt32 y);
WindowPosition getWindowPosition();

void setWindowSize(UInt32 w, UInt32 h);
WindowSize getWindowSize();

void adjustWindow(UInt32 x, UInt32 y, UInt32 w, UInt32 h);

void setViewportPosition(UInt32 x, UInt32 y);
ViewportPosition getViewportPosition();

void setViewportSize(UInt32 w, UInt32 h);
ViewportSize getViewportSize();

void adjustViewport();
void adjustViewport(UInt32 x, UInt32 y, UInt32 w, UInt32 h);

void setBackgroundColor(Int16 r, Int16 g, Int16 b, Int16 a);
BackgroundColor getBackgroundColor();

bool getIsStarting();
bool getIsReadyForUse();
bool getIsStopping();

bool getUserHasXedOut();

// Functions.
void start();
void stop();
void startFrame();
void endFrame();

// Exceptions.
class StartFailure {
public:
    StartFailure();
    StartFailure(const char *extraInfo);
    ~StartFailure() {}

    const char *what() const throw();

private:
    const char *extraInfo_;
};

} // Engine name space.
} // MatVGL name space.

#endif // MATVGL_ENGINE_HPP

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

//////////////////////////////////////////////////////////////////////////////
/// \file MatVGL_Engine.hpp
/// \brief Header file for the game engine.
///
/// Takes care of declaring the variables and functions that the game engine
/// needs.
//////////////////////////////////////////////////////////////////////////////

#ifndef MATVGL_ENGINE_HPP
#define MATVGL_ENGINE_HPP

#include "MatVGL_Setup.hpp" ///< We need to read the setup for the library.

//////////////////////////////////////////////////////////////////////////////
/// \namespace MatVGL
///
/// Namespace of the library.
//////////////////////////////////////////////////////////////////////////////
namespace MatVGL {
//////////////////////////////////////////////////////////////////////////////
/// \namespace Engine
///
/// Namespace of the engine.
//////////////////////////////////////////////////////////////////////////////
namespace Engine {

// The variables needed.
MatVGL_Window *window = nullptr;           ///< The window that will be open.
const char *windowTitle = "MatVGL Window"; ///< The window title.
MatVGL_Context context = 0;                ///< The context to render to.
MatVGL_Event event;                        ///< The window events.

bool isStarting = false;    ///< Whether the engine is starting or not.
bool isReadyForUse = false; ///< Whether the engine is ready for use or not.
bool isStopping = false;    ///< Whether the engine is stopping or not.

//////////////////////////////////////////////////////////////////////////////
/// \struct WindowPosition
/// \brief The WindowPosition structure.
///
/// A structure that holds the X and Y coordinates of the window on the screen.
//////////////////////////////////////////////////////////////////////////////
struct WindowPosition {
  UInt32 x = 0;
  UInt32 y = 0;
} windowPosition;

//////////////////////////////////////////////////////////////////////////////
/// \struct WindowSize
/// \brief The WindowSize structure.
///
/// A structure that holds the Width and Height of the window on the screen.
//////////////////////////////////////////////////////////////////////////////
struct WindowSize {
  UInt32 w = 0;
  UInt32 h = 0;
} windowSize;

//////////////////////////////////////////////////////////////////////////////
/// \struct ViewportPosition
/// \brief The ViewportPosition structure.
///
/// A structure that holds the X and Y coordinates of the viewport for the
/// window.
//////////////////////////////////////////////////////////////////////////////
struct ViewportPosition {
  UInt32 x = 0;
  UInt32 y = 0;
} viewportPosition;

//////////////////////////////////////////////////////////////////////////////
/// \struct ViewportSize
/// \brief The ViewportSize structure.
///
/// A structure that holds the Width and Height of the viewport for the window.
//////////////////////////////////////////////////////////////////////////////
struct ViewportSize {
  UInt32 w = 0;
  UInt32 h = 0;
} viewportSize;

//////////////////////////////////////////////////////////////////////////////
/// \struct BackgroundColor
/// \brief The BackgroundColor structure.
///
/// A structure that holds the Red, Green, Blue and Alpha values for the
/// background color of the window.
//////////////////////////////////////////////////////////////////////////////
struct BackgroundColor {
  Int16 r = 255;
  Int16 g = 255;
  Int16 b = 255;
  Int16 a = 255;
} bgColor;

// Setters and getters for the variables.
//////////////////////////////////////////////////////////////////////////////
/// \fn voidSetWindowTitle(const char *title)
/// \brief Set the window title.
/// \param title a constant character pointer with the window title.
//
/// Sets the title of the window and updates the title of the window if such
/// window already exists, using the given parameter.
//////////////////////////////////////////////////////////////////////////////
void setWindowTitle(const char *title);
//////////////////////////////////////////////////////////////////////////////
/// \fn const char *getWindowTitle()
/// \brief Returns the title of the window.
/// \return The window title.
///
/// Returns the current title of the window.
//////////////////////////////////////////////////////////////////////////////
const char *getWindowTitle();

//////////////////////////////////////////////////////////////////////////////
/// \fn void setWindowPosition(UInt32 x, UInt32 y)
/// \brief Sets the position of the window on the screen.
/// \param x an unsigned integer of size 32 with the X coordinate.
/// \param y an unsigned integer of size 32 with the Y coordinate.
///
/// Sets the window position on the screen, updating such window's position if
/// it exists, by using the given X and Y coordinates.
//////////////////////////////////////////////////////////////////////////////
void setWindowPosition(UInt32 x, UInt32 y);
//////////////////////////////////////////////////////////////////////////////
/// \fn WindowPosition getWindowPosition()
/// \brief Returns the window position.
/// \return The window position.
///
/// Returns a structure that holds the X and Y coordinates of the window on the
/// screen.
//////////////////////////////////////////////////////////////////////////////
WindowPosition getWindowPosition();

//////////////////////////////////////////////////////////////////////////////
/// \fn void setWindowSize(UInt32 w, UInt32 h)
/// \brief Sets the size of the window.
/// \param w an unsigned integer of size 32 with the width.
/// \param h an unsigned integer of size 32 with the height.
///
/// Sets the window width and height, updating such window's position if it
/// exists, by using the given Width and Height.
//////////////////////////////////////////////////////////////////////////////
void setWindowSize(UInt32 w, UInt32 h);
//////////////////////////////////////////////////////////////////////////////
/// \fn
/// \brief Returns the window size.
/// \return The window size.
///
/// Returns a structure that holds the Width and Height of the window.
//////////////////////////////////////////////////////////////////////////////
WindowSize getWindowSize();

//////////////////////////////////////////////////////////////////////////////
/// \brief Adjusts the window position on the screen and size.
/// \param x an unsigned integer of size 32 with the X coordinate.
/// \param y an unsigned integer of size 32 with the Y coordinate.
/// \param w an unsigned integer of size 32 with the width.
/// \param h an unsigned integer of size 32 with the height.
///
/// Sets the window X and Y coordinates, as well as its width and height, and
/// updates it if such window already exists, by using the given parameters.
//////////////////////////////////////////////////////////////////////////////
void adjustWindow(UInt32 x, UInt32 y, UInt32 w, UInt32 h);

//////////////////////////////////////////////////////////////////////////////
/// \brief Sets the viewport position on the window.
/// \param x an unsigned integer of size 32 with the X coordinate.
/// \param y an unsigned integer of size 32 with the Y coordinate.
///
/// Sets the viewport position on the window by using the given X and Y
/// coordinates.
//////////////////////////////////////////////////////////////////////////////
void setViewportPosition(UInt32 x, UInt32 y);
//////////////////////////////////////////////////////////////////////////////
/// \brief Returns the viewport position.
/// \return The viewport position.
///
/// Returns a structure that holds the X and Y coordinates of the viewport on
/// the window.
//////////////////////////////////////////////////////////////////////////////
ViewportPosition getViewportPosition();

//////////////////////////////////////////////////////////////////////////////
/// \brief Sets the viewport size.
/// \param w an unsigned integer of size 32 with the width.
/// \param h an unsigned integer of size 32 with the height.
///
/// Sets the viewport size by using the given Width and Height parameters.
//////////////////////////////////////////////////////////////////////////////
void setViewportSize(UInt32 w, UInt32 h);
//////////////////////////////////////////////////////////////////////////////
/// \brief Returns the viewport size.
/// \return The viewport size.
///
/// Returns a structure that holds the Width and Height of the viewport.
//////////////////////////////////////////////////////////////////////////////
ViewportSize getViewportSize();

//////////////////////////////////////////////////////////////////////////////
/// \brief Adjusts the viewport position and size automatically.
///
/// Repositions the viewport on the (0, 0) coordinates of the window and sets
/// its size to fit the one of the window, completely covering the window. This
/// makes the viewport and the window have the same size parameters, while the
/// viewport will always be at position (0, 0).
//////////////////////////////////////////////////////////////////////////////
void adjustViewport();
//////////////////////////////////////////////////////////////////////////////
/// \brief Adjusts the viewport position and size.
/// \param x an unsigned integer of size 32 with the X coordinate.
/// \param y an unsigned integer of size 32 with the Y coordinate.
/// \param w an unsigned integer of size 32 with the width.
/// \param h an unsigned integer of size 32 with the height.
/// \warning This is an overriden function of "void adjustViewport();"
///
/// Sets the viewport X and Y coordinates, as well as its width and height, by
/// using the given parameters.
//////////////////////////////////////////////////////////////////////////////
void adjustViewport(UInt32 x, UInt32 y, UInt32 w, UInt32 h);

//////////////////////////////////////////////////////////////////////////////
/// \brief Sets the background color.
/// \param r an integer of size 16 with the Red value.
/// \param g an integer of size 16 with the Green value.
/// \param b an integer of size 16 with the Blue value.
/// \param a an integer of size 16 with the Alpha value.
///
/// Sets the background color of the window and updates it. uses the 0-255
/// numbers instead of 0.0-1.0 so that it's easier for the user to select the
/// correct color, not having to deal with floats. The function will take care
/// to transform the values to floats when and if needed.
//////////////////////////////////////////////////////////////////////////////
void setBackgroundColor(Int16 r, Int16 g, Int16 b, Int16 a);
//////////////////////////////////////////////////////////////////////////////
/// \brief Returns the background color of the window.
/// \return The background color.
///
/// Returns a structure that holds the color values for the background color.
//////////////////////////////////////////////////////////////////////////////
BackgroundColor getBackgroundColor();

//////////////////////////////////////////////////////////////////////////////
/// \brief Returns whether the engine is starting.
/// \return Whether the engine is starting.
///
/// Returns whether the engine is starting or not.
//////////////////////////////////////////////////////////////////////////////
bool getIsStarting();
//////////////////////////////////////////////////////////////////////////////
/// \brief Returns wehther the engine is ready for use.
/// \return Whether the engine is ready for use.
///
/// Returns whether the engine is ready for use or not.
//////////////////////////////////////////////////////////////////////////////
bool getIsReadyForUse();
//////////////////////////////////////////////////////////////////////////////
/// \brief Returns whether the engine is stopping.
/// \return Whether the engine is stopping.
///
/// Returns whether the engine is stopping or not.
//////////////////////////////////////////////////////////////////////////////
bool getIsStopping();

//////////////////////////////////////////////////////////////////////////////
/// \brief Returns whether the user has Xed out the window.
/// \return Whether the user has Xed out the window.
///
/// Returns whether the user has Xed out the window or not.
//////////////////////////////////////////////////////////////////////////////
bool getUserHasXedOut();

// Functions.
//////////////////////////////////////////////////////////////////////////////
/// \brief Starts the engine.
///
/// Takes care of initializing the needed graphic modules and finishes opening
/// the window and preparing it for usage.
//////////////////////////////////////////////////////////////////////////////
void start();
//////////////////////////////////////////////////////////////////////////////
/// \brief Stops the engine.
///
/// Takes care of stopping the engine, deleting any created pointers or used
/// modules, as well as destroying the context for rendering and the window
/// itself, exiting the engine.
//////////////////////////////////////////////////////////////////////////////
void stop();
//////////////////////////////////////////////////////////////////////////////
/// \brief Starts a frame.
/// \warning Works in conjuction with "void endFrame();" and is meant to work in
/// the beginning of the rendering in the game loop.
///
/// Prepares a frame to be started, clearing the buffers so that they can have
/// data rendered onto them.
//////////////////////////////////////////////////////////////////////////////
void startFrame();
//////////////////////////////////////////////////////////////////////////////
/// \brief Ends a frame.
/// \warning Works in conjuction with "void startFrame();" and is meant to work
/// in the end of the rendering of the game loop.
///
/// Finishes any neede preparations for showing the rendered items and swaps the
/// window buffers, making them visible.
//////////////////////////////////////////////////////////////////////////////
void endFrame();

// Exceptions.
//////////////////////////////////////////////////////////////////////////////
/// \class StartFailure
/// \brief The StartFailure class.
///
/// Exceptions class that should be used to throw exceptions during the engine
/// start up.
//////////////////////////////////////////////////////////////////////////////
class StartFailure {
public:
  //////////////////////////////////////////////////////////////////////////////
  /// \brief Constructor of the StartFailure class.
  ///
  /// Constructor for the StartFailure class. It takes care of logging the
  /// exception.
  //////////////////////////////////////////////////////////////////////////////
  StartFailure();
  //////////////////////////////////////////////////////////////////////////////
  /// \brief Constructor of the StartFailure class.
  /// \param extraInfo a constant character pointer with extra information.
  ///
  /// Constructor for the StartFailure class. It takes care of adding extra
  /// information for the exception and logging it.
  //////////////////////////////////////////////////////////////////////////////
  StartFailure(const char *extraInfo);
  //////////////////////////////////////////////////////////////////////////////
  /// \brief Destructor for the class.
  ///
  /// A destructor for the StartFailure class. There's no need to do any extra
  /// functions in it.
  //////////////////////////////////////////////////////////////////////////////
  ~StartFailure() {}

  //////////////////////////////////////////////////////////////////////////////
  /// \brief Gets the information of the exception.
  /// \return The string with the information of the exception.
  ///
  /// Returns the information of the exception so that it can be read and/or
  /// printed by the user.
  //////////////////////////////////////////////////////////////////////////////
  const char *what() const throw();

private:
  const char *extraInfo_; ///< Extra information for the exception.
};

} // Engine name space.
} // MatVGL name space.

#endif // MATVGL_ENGINE_HPP

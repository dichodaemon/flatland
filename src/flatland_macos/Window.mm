#include "Window.h"
#import "ApplicationDelegate.h"
#include <flatland/GraphicsContext.h>
#include <flatland/Conversion.h>
#include <flatland/Logger.h>

using Flatland::toString;

//------------------------------------------------------------------------------

Window::Window( Flatland::Bus & bus, size_t width, size_t height )
  : _bus( bus ),
    _width( width ),
    _height( height )
{
  // Flatland::Logger::info(
  //   "Initializing window ("
  //     + toString( width ) + "x" + toString( height ) + ")",
  //   "COCOA"
  // );
  // _surface = SDL_SetVideoMode( width, height, 32, SDL_OPENGL );
}

//------------------------------------------------------------------------------

double
Window::width()
{
  return _width;
}

//------------------------------------------------------------------------------

double
Window::height()
{
  return _height;
}

//------------------------------------------------------------------------------

void
Window::display( Flatland::GraphicsContextBase & graphics )
{
}

//------------------------------------------------------------------------------

void
Window::flip()
{
  [_delegate flip];
}

//------------------------------------------------------------------------------

void
Window::run( double frequency )
{
  Flatland::Logger::info( "Configuring COCOA Main Loop", "COCOA" );
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  [NSApplication sharedApplication];
  
  _delegate = [
    [ApplicationDelegate alloc] 
    initWithBus: &_bus
    andWidth: _width
    andHeight: _height
    andFps: frequency
  ];
  
  [_delegate run];

  [pool release];
  [_delegate release];
  Flatland::Logger::info( "Terminating COCOA Main Loop", "COCOA" );
}

//------------------------------------------------------------------------------

Flatland::WindowBase *
newWindow( Flatland::Bus & bus, size_t width, size_t height )
{
  return new Window( bus, width, height );
}


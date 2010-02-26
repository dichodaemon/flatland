#include "Screen.h"
#include "ClassLoader.h"
#include "GraphicsContextBase.h"
#include "GraphicsContext.h"

//------------------------------------------------------------------------------

Flatland::Screen::Screen( size_t width, size_t height )
  : _impl( ClassLoader<ScreenBase>::loadFactory( "newScreen" )( width, height ) )
{
}

//------------------------------------------------------------------------------

Flatland::Screen::~Screen()
{
  delete _impl;
}

//------------------------------------------------------------------------------

double
Flatland::Screen::width()
{
  return _impl->width();
}

//------------------------------------------------------------------------------

double
Flatland::Screen::height()
{
  return _impl->height();
}
//------------------------------------------------------------------------------

void
Flatland::Screen::flip()
{
  _impl->flip();
}

//------------------------------------------------------------------------------

void
Flatland::Screen::display( GraphicsContextBase & graphics )
{
  if ( GraphicsContext * g = dynamic_cast< GraphicsContext * >( &graphics ) )
  {
    _impl->display( *( g->_impl ) );
  }
}

#include "Window.h"
#include "GraphicsContextBase.h"
#include "GraphicsContext.h"

//------------------------------------------------------------------------------

Flatland::Window::Window( Bus & bus, size_t width, size_t height )
  : _impl( newWindow( bus, width, height ) )
{
}

//------------------------------------------------------------------------------

Flatland::Window::~Window()
{
  delete _impl;
}

//------------------------------------------------------------------------------

double
Flatland::Window::width()
{
  return _impl->width();
}

//------------------------------------------------------------------------------

double
Flatland::Window::height()
{
  return _impl->height();
}
//------------------------------------------------------------------------------

void
Flatland::Window::flip()
{
  _impl->flip();
}

//------------------------------------------------------------------------------

void
Flatland::Window::display( GraphicsContextBase & graphics )
{
  if ( GraphicsContext * g = dynamic_cast< GraphicsContext * >( &graphics ) )
  {
    _impl->display( *( g->_impl ) );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Window::run( double frequency )
{
  _impl->run( frequency );
}


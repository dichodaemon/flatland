#include "Screen.h"
#include "GraphicsContext.h"
#include <flatland/GraphicsContext.h>
#include <flatland/Conversion.h>
#include <flatland/Logger.h>

using Flatland::toString;

//------------------------------------------------------------------------------

Screen::Screen( size_t width, size_t height )
{
  Flatland::Logger::info(
    "Initializing screen ("
      + toString( width ) + "x" + toString( height ) + ")",
    "SDL"
  );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
//   _surface = SDL_SetVideoMode( width, height, 32, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF );
  _surface = SDL_SetVideoMode( width, height, 32, SDL_OPENGL );
}

//------------------------------------------------------------------------------

double
Screen::width()
{
  return _surface->w;
}

//------------------------------------------------------------------------------

double
Screen::height()
{
  return _surface->h;
}

//------------------------------------------------------------------------------

void
Screen::display( Flatland::GraphicsContextBase & graphics )
{
/*  if ( GraphicsContext * g = dynamic_cast< GraphicsContext * >( &graphics ) )
  {
    SDL_BlitSurface( g->_surface, NULL, _surface, NULL );
  }*/
}

//------------------------------------------------------------------------------

void
Screen::flip()
{
  SDL_GL_SwapBuffers();
}

//------------------------------------------------------------------------------

Flatland::ScreenBase *
newScreen( size_t width, size_t height )
{
  return new Screen( width, height );
}


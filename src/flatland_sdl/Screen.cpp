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
  _surface = SDL_SetVideoMode( width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
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
  if ( GraphicsContext * g = dynamic_cast< GraphicsContext * >( &graphics ) )
  {
    SDL_BlitSurface( g->_surface, NULL, _surface, NULL );
  }
}

//------------------------------------------------------------------------------

void
Screen::flip()
{
  SDL_Flip( _surface );
}

//------------------------------------------------------------------------------

Flatland::ScreenBase *
newScreen( size_t width, size_t height )
{
  return new Screen( width, height );
}


#include "GraphicsContext.h"
#include "Screen.h"
#include <flatland/Color.h>
extern "C" {
  #include <SDL/SDL_gfxPrimitives.h>
}

//------------------------------------------------------------------------------

GraphicsContext::GraphicsContext( Screen & screen )
  : _surface( screen._surface ),
    _owner( false )
{
}

//------------------------------------------------------------------------------

GraphicsContext::GraphicsContext( size_t width, size_t height )
  : _owner( true )
{
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  _surface = SDL_CreateRGBSurface(
    SDL_HWSURFACE,
    width, height, 32,
    rmask, gmask, bmask, amask
  );
}

//------------------------------------------------------------------------------

GraphicsContext::~GraphicsContext()
{
  if ( _owner )
  {
    SDL_FreeSurface( _surface );
  }
}

//------------------------------------------------------------------------------

double
GraphicsContext::width()
{
  return _surface->w;
}

//------------------------------------------------------------------------------

double
GraphicsContext::height()
{
  return _surface->h;
}

//------------------------------------------------------------------------------

void
GraphicsContext::drawCircle(
  double x,
  double y,
  double radius,
  const Flatland::Color & color,
  size_t thickness
)
{
  aaellipseColor( _surface, x, y, radius, radius, color );
}

//------------------------------------------------------------------------------

void
GraphicsContext::fillCircle(
  double x,
  double y,
  double radius,
  const Flatland::Color & color
)
{
  filledEllipseColor( _surface, x, y, radius, radius, color );
}

//------------------------------------------------------------------------------

void
GraphicsContext::drawLine(
  double x1,
  double y1,
  double x2,
  double y2,
  const Flatland::Color & color,
  size_t thickness
)
{
  aalineColor( _surface, x1, y1, x2, y2, color );
}

//------------------------------------------------------------------------------

void
GraphicsContext::clear( const Flatland::Color & color )
{
  SDL_FillRect(
    _surface, NULL,
    SDL_MapRGBA(
      _surface->format,
      color.red(), color.green(), color.blue(), color.alpha()
    )
  );
}

//------------------------------------------------------------------------------

Flatland::GraphicsContextBase *
newGraphicsContext( size_t width, size_t height )
{
  return new GraphicsContext( width, height );
}

//------------------------------------------------------------------------------

Flatland::GraphicsContextBase *
newGraphicsContextFromScreen( Screen & screen )
{
  return new GraphicsContext( screen );
}

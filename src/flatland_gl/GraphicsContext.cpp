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
  GLfloat vertices[2 * 3] = {
    x1, y1, 0,
    x2, y2, 0
  };
  
  GLubyte colors[2 * 4] = {
    color.red(), color.green(), color.blue(), color.alpha(),
    color.red(), color.green(), color.blue(), color.alpha()
  };

  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_COLOR_ARRAY );
  
  glVertexPointer( 3, GL_FLOAT, 0, vertices );
  glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colors );
  glDrawArrays( GL_LINES, 0, 2 );
}

//------------------------------------------------------------------------------

void
GraphicsContext::clear( const Flatland::Color & color )
{
  glViewport( 0, 0, width(), height() );
  glClearColor( color.red(), color.green(), color.blue(), color.alpha() );
  glClear( GL_COLOR_BUFFER_BIT );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -width() / 2.0, width() / 2.0, -height() / 2.0, height() / 2.0, -1.0f, 1.0f );
  glMatrixMode( GL_MODELVIEW );
  glColor3f(0.0f, 1.0f, 0.0f);
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

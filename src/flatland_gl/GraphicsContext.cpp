#include "GraphicsContext.h"
#include <flatland/Color.h>
#include <Flatland/Logger.h>
#include <flatland/Window.h>

#if defined (__APPLE__)
  #import <OpenGL/OpenGL.h>
#elif defined ( __linux )
  #include <GL/gl.h>
#endif

#include <cstdio>

using Flatland::WindowBase;

//------------------------------------------------------------------------------

GraphicsContext::GraphicsContext( WindowBase & screen )
  : _owner( false ),
    _width( screen.width() ),
    _height( screen.height() )
{
}

//------------------------------------------------------------------------------

GraphicsContext::GraphicsContext( size_t width, size_t height )
  : _owner( true )
{
}

//------------------------------------------------------------------------------

GraphicsContext::~GraphicsContext()
{
}

//------------------------------------------------------------------------------

double
GraphicsContext::width()
{
  return _width;
}

//------------------------------------------------------------------------------

double
GraphicsContext::height()
{
  return _height;
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
  Flatland::Logger::debug( "Drawing line", "OpenGL" );
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
newGraphicsContextFromWindow( Flatland::WindowBase & screen )
{
  return new GraphicsContext( screen );
}

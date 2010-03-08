#include "GraphicsContext.h"
#include "Image.h"
#include <flatland/Color.h>
#include <flatland/Image.h>
#include <flatland/Logger.h>
#include <flatland/Transform.h>
#include <flatland/Vector2D.h>
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

  glEnableClientState( GL_COLOR_ARRAY );
  
  glVertexPointer( 3, GL_FLOAT, 0, vertices );
  glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colors );
  glDrawArrays( GL_LINES, 0, 2 );

  glDisableClientState( GL_COLOR_ARRAY );
}

//------------------------------------------------------------------------------

void 
GraphicsContext::drawImage( 
  const Flatland::Image & image, 
  const Flatland::Transform & transform, 
  double width, 
  double height 
)
{
  double hw = 0.5 * width;
  double hh = 0.5 * height;
  
  Flatland::Vector2D p1 = toGraphics( transform.toRoot( Flatland::Vector2D( -hw, -hh ) ) );
  Flatland::Vector2D p2 = toGraphics( transform.toRoot( Flatland::Vector2D(  hw, -hh ) ) );
  Flatland::Vector2D p3 = toGraphics( transform.toRoot( Flatland::Vector2D(  hw,  hh ) ) );
  Flatland::Vector2D p4 = toGraphics( transform.toRoot( Flatland::Vector2D( -hw,  hh ) ) );
  // Flatland::Vector2D p1( -100, -100 );
  // Flatland::Vector2D p2(  100, -100 );
  // Flatland::Vector2D p3(  100,  100 );
  // Flatland::Vector2D p4( -100,  100 );
  
  GLfloat vertices[4 * 3] = {
    p1.x(), p1.y(), 0,
    p2.x(), p2.y(), 0,
    p3.x(), p3.y(), 0,
    p4.x(), p4.y(), 0
  };  
  
  GLfloat texcoords[4 * 2] = {
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0, 
    0.0, 0.0
  };
  
  GLubyte indices[4]={0, 1, 3, 2};

  const Image * glImage = dynamic_cast< const Image* >( image.implementation() );
  
  glBindTexture( GL_TEXTURE_2D, glImage->index() );

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
  glVertexPointer( 3, GL_FLOAT, 0, vertices );
  glTexCoordPointer( 2, GL_FLOAT, 0, texcoords );  

  glEnable( GL_TEXTURE_2D );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );  
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glDrawElements( GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices );

  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
  glDisable( GL_TEXTURE_2D );
}

//------------------------------------------------------------------------------

void
GraphicsContext::clear( const Flatland::Color & color )
{
  glViewport( 0, 0, width(), height() );
  glClearColor( color.red(), color.green(), color.blue(), color.alpha() );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -width() / 2.0, width() / 2.0, -height() / 2.0, height() / 2.0, -1.0f, 1.0f );
  glMatrixMode( GL_MODELVIEW );
  
  glDisable( GL_LIGHTING );
  glEnable( GL_BLEND );
  
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
  glEnableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
  glDisableClientState( GL_COLOR_ARRAY );  
  glDisableClientState( GL_NORMAL_ARRAY );  
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

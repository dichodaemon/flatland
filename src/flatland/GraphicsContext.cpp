#include "GraphicsContext.h"
#include "ClassLoader.h"
#include "Vector2D.h"
#include "Screen.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::GraphicsContext::GraphicsContext( size_t width, size_t height )
  : _impl( ClassLoader<GraphicsContextBase>::loadFactory( "newGraphicsContext" )( width, height )  ),
    _p1( -width / 2.0, -height / 2.0 ),
    _dX( 1 ),
    _dY( 1 )
{
}

//------------------------------------------------------------------------------

Flatland::GraphicsContext::GraphicsContext( Screen & screen )
  : _impl( ClassLoader<GraphicsContextBase>::loadFactory<ScreenFactory>( "newGraphicsContextFromScreen" )( *( screen._impl ) ) ),
    _p1( -screen.width() / 2.0, -screen.height() / 2.0 ),
    _dX( 1 ),
    _dY( 1 )
{
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::setTransform( const Vector2D & center, double rotation, double width  )
{
  double height = width * this->height() / this->width();
  _p1.x( center.x() - width / 2.0 );
  _p1.y( center.y() - height / 2.0 );
  _dX = this->width()  / width;
  _dY = this->height() / height;
}

//------------------------------------------------------------------------------

double
Flatland::GraphicsContext::width()
{
  return _impl->width();
}

//------------------------------------------------------------------------------

double
Flatland::GraphicsContext::height()
{
  return _impl->height();
}

//------------------------------------------------------------------------------

Vector2D
Flatland::GraphicsContext::toGraphics( const Vector2D & vector )
{
  return  Vector2D( ( vector.x() - _p1.x() ) * _dX, ( vector.y() - _p1.y() ) * _dY );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::GraphicsContext::toWorld( const Vector2D & vector )
{
  double dX = 1.0 / _dX;
  double dY = 1.0 / _dY;
  return  Vector2D( vector.x() * dX + _p1.x(), vector.y() * dY + _p1.y() );
}

//------------------------------------------------------------------------------

Flatland::GraphicsContext::~GraphicsContext()
{
  delete _impl;
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::drawCircle(
  double x,
  double y,
  double radius,
  const Color & color,
  size_t thickness
)
{
  Vector2D v = toGraphics( Vector2D( x, y ) );
  _impl->drawCircle( v.x(), v.y(), radius * _dX, color, thickness );
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::drawCircle(
  double x,
  double y,
  double radius,
  const Color & color,
  size_t thickness,
  bool imageCoordinates
)
{
  if ( imageCoordinates )
  {
    _impl->drawCircle( x, y, radius, color, thickness );
  }
  else
  {
    Vector2D v = toGraphics( Vector2D( x, y ) );
    _impl->drawCircle( v.x(), v.y(), radius * _dX, color, thickness );
  }
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::fillCircle(
  double x,
  double y,
  double radius,
  const Color & color,
  bool imageCoordinates
)
{
  if ( imageCoordinates )
  {
    _impl->fillCircle( x, y, radius, color );
  }
  else
  {
    Vector2D v = toGraphics( Vector2D( x, y ) );
    _impl->fillCircle( v.x(), v.y(), radius * _dX, color );
  }
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::fillCircle(
  double x,
  double y,
  double radius,
  const Color & color
)
{
  Vector2D v = toGraphics( Vector2D( x, y ) );
  _impl->fillCircle( v.x(), v.y(), radius * _dX, color );
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::drawLine(
  double x1,
  double y1,
  double x2,
  double y2,
  const Color & color,
  size_t thickness,
  bool imageCoordinates
)
{
  if ( imageCoordinates )
  {
    _impl->drawLine( x1, y1, x2, y2, color, thickness );
  }
  else
  {
    Vector2D v1 = toGraphics( Vector2D( x1, y1 ) );
    Vector2D v2 = toGraphics( Vector2D( x2, y2 ) );
    _impl->drawLine( v1.x(), v1.y(), v2.x(), v2.y(), color, thickness );
  }
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::drawLine(
  double x1,
  double y1,
  double x2,
  double y2,
  const Color & color,
  size_t thickness
)
{
  Vector2D v1 = toGraphics( Vector2D( x1, y1 ) );
  Vector2D v2 = toGraphics( Vector2D( x2, y2 ) );
  _impl->drawLine( v1.x(), v1.y(), v2.x(), v2.y(), color, thickness );
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::clear( const Color & color )
{
  _impl->clear( color );
}

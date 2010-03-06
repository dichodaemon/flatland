#include "GraphicsContext.h"
#include "Vector2D.h"
#include "Window.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::GraphicsContext::GraphicsContext( size_t width, size_t height )
  : _impl( newGraphicsContext( width, height )  )
{
}

//------------------------------------------------------------------------------

Flatland::GraphicsContext::GraphicsContext( Window & screen )
  : _impl( newGraphicsContextFromWindow( *( screen._impl ) ) )
{
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContext::setTransform( const Vector2D & center, double rotation, double width  )
{
  _transform.translation( center );
  _transform.rotation( rotation );
  double scale = width / this->width();
  _transform.scale( Vector2D( scale, scale ) );
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
  return  _transform.fromParent( vector );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::GraphicsContext::toWorld( const Vector2D & vector )
{
  return  _transform.toParent( vector );
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
  _impl->drawCircle(
    v.x(), v.y(),
    radius * _transform.scale().x(),
    color, thickness
  );
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
    _impl->drawCircle(
      v.x(), v.y(),
      radius * _transform.scale().x(),
      color, thickness );
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
    _impl->fillCircle(
      v.x(), v.y(),
      radius * _transform.scale().x(),
      color
    );
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
  _impl->fillCircle(
    v.x(), v.y(),
    radius * _transform.scale().x(),
    color
  );
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

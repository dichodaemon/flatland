#include "GraphicsContextBase.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::GraphicsContextBase::~GraphicsContextBase()
{
}

//------------------------------------------------------------------------------

void
Flatland::GraphicsContextBase::setTransform( const Vector2D & center, double rotation, double width  )
{
  _transform.translation( center );
  _transform.rotation( rotation );
  double scale = width / this->width();
  _transform.scale( Vector2D( scale, scale ) );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::GraphicsContextBase::toGraphics( const Vector2D & vector )
{
  return  _transform.fromParent( vector );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::GraphicsContextBase::toWorld( const Vector2D & vector )
{
  return  _transform.toParent( vector );
}

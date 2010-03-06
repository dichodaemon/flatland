#include "Vector2D.h"

//------------------------------------------------------------------------------

Flatland::Vector2D::Vector2D()
{
  _vector.x = 0;
  _vector.y = 0;
}

//------------------------------------------------------------------------------

Flatland::Vector2D::Vector2D( double angle )
{
  _vector = cpvforangle( angle );
}

//------------------------------------------------------------------------------

Flatland::Vector2D::Vector2D( const Vector2D & other )
{
  _vector = other._vector;
}

//------------------------------------------------------------------------------

Flatland::Vector2D::Vector2D( double x, double y )
{
  _vector.x = x;
  _vector.y = y;
}

//------------------------------------------------------------------------------

Flatland::Vector2D::Vector2D( const cpVect & vector )
{
  _vector = vector;
}


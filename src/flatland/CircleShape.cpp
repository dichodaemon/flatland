#include "CircleShape.h"

//------------------------------------------------------------------------------

Flatland::CircleShape::CircleShape(
  Body & body,
  double radius,
  const Vector2D & offset,
  bool fixed
)
  : Shape( cpCircleShapeNew( body, radius, offset ), fixed )
{
}

//------------------------------------------------------------------------------

double
Flatland::CircleShape::radius() const
{
  return cpCircleShapeGetRadius( _shape );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::CircleShape::offset() const
{
  return cpCircleShapeGetOffset( _shape );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::CircleShape::worldOffset() const
{
  return body().toWorld( cpCircleShapeGetOffset( _shape ) );
}

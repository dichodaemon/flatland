#include "SegmentShape.h"

//------------------------------------------------------------------------------

Flatland::SegmentShape::SegmentShape(
  Body & body,
  const Vector2D & v1,
  const Vector2D & v2,
  double thickness,
  bool fixed
)
  : Shape( cpSegmentShapeNew( body, v1, v2, thickness ), fixed )
{
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SegmentShape::v1() const
{
  return cpSegmentShapeGetA( _shape );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SegmentShape::v2() const
{
  return cpSegmentShapeGetB( _shape );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SegmentShape::worldV1() const
{
  return body().toWorld( cpSegmentShapeGetA( _shape ) );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SegmentShape::worldV2() const
{
  return body().toWorld( cpSegmentShapeGetB( _shape ) );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SegmentShape::normal() const
{
  return cpSegmentShapeGetNormal( _shape );
}

//------------------------------------------------------------------------------

double
Flatland::SegmentShape::thickness() const
{
  return cpSegmentShapeGetRadius( _shape );
}


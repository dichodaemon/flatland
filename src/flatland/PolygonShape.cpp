#include "PolygonShape.h"

//------------------------------------------------------------------------------

Flatland::PolygonShape::PolygonShape(
  Body & body,
  const VertexList & vertices,
  const Vector2D & offset,
  bool fixed
)
  : Shape( cpPolyShapeNew(
            body, vertices.size(),
            const_cast<cpVect*>( &( vertices[0] ) ),
            offset),
          fixed )
{
}

//------------------------------------------------------------------------------

int
Flatland::PolygonShape::size() const
{
  return cpPolyShapeGetNumVerts( _shape );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::PolygonShape::vertex( int i ) const
{
  return cpPolyShapeGetVert( _shape, i );
}

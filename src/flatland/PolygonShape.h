#ifndef FLATLAND_POLYGON_SHAPE_H
#define FLATLAND_POLYGON_SHAPE_H


#include "Vector2D.h"
#include "Shape.h"
#include "vector"


namespace Flatland
{


class PolygonShape : public Shape
{
public:
  typedef std::vector<cpVect> VertexList;
  
  PolygonShape(
    Body & body,
    const VertexList & vertices,
    const Vector2D & offset,
    bool fixed = false
  );

  int size() const;
  Vector2D vertex( int i ) const;
};


}


#endif //FLATLAND_POLYGON_SHAPE_H

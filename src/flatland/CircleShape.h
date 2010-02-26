#ifndef FLATLAND_CIRCLE_SHAPE_H
#define FLATLAND_CIRCLE_SHAPE_H


#include "Shape.h"


namespace Flatland
{


class CircleShape : public Shape
{
public:
  CircleShape( Body & body, double radius, const Vector2D & offset, bool fixed = false );

  double radius() const;
  Vector2D offset() const;

  Vector2D worldOffset() const;
};


}


#endif //FLATLAND_CIRCLE_SHAPE_H

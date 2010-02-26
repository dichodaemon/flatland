#ifndef FLATLAND_SEGMENT_SHAPE_H
#define FLATLAND_SEGMENT_SHAPE_H


#include "Shape.h"


namespace Flatland
{


class SegmentShape : public Shape
{
public:
  SegmentShape(
    Body & body,
    const Vector2D & v1,
    const Vector2D & v2,
    double thickness,
    bool fixed = false
  );

  Vector2D v1() const;
  Vector2D v2() const;
  Vector2D worldV1() const;
  Vector2D worldV2() const;
  Vector2D normal() const;
  double thickness() const;
};


}


#endif //FLATLAND_SEGMENT_SHAPE_H

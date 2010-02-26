#ifndef FLATLAND_PIVOT_JOINT_H
#define FLATLAND_PIVOT_JOINT_H


#include "Constraint.h"


namespace Flatland
{


class PivotJoint : public Constraint
{
public:
  PivotJoint( Body & body1, Body & body2, const Vector2D & pivot );
  PivotJoint(
    Body & body1,
    Body & body2,
    const Vector2D & anchor1,
    const Vector2D & anchor2
  );
  Vector2D anchor1();
  void anchor1( const Vector2D & value );
  Vector2D anchor2();
  void anchor2( const Vector2D & value );
};


}


#endif //FLATLAND_PIVOT_JOINT_H
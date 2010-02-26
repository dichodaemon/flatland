#ifndef FLATLAND_SLIDE_JOINT_H
#define FLATLAND_SLIDE_JOINT_H


#include "Constraint.h"


namespace Flatland
{


class SlideJoint : public Constraint
{
public:
  SlideJoint(
    Body & body1,
    Body & body2,
    const Vector2D & anchor1,
    const Vector2D & anchor2,
    double min,
    double max
  );
  Vector2D anchor1();
  void anchor1( const Vector2D & value );
  Vector2D anchor2();
  void anchor2( const Vector2D & value );
  double min() const;
  void min( double value );
  double max() const;
  void max( double value );
};


}


#endif //FLATLAND_SLIDE_JOINT_H
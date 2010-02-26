#ifndef FLATLAND_PIN_JOINT_H
#define FLATLAND_PIN_JOINT_H


#include "Constraint.h"


namespace Flatland
{


class PinJoint : public Constraint
{
public:
  PinJoint( Body & body1, Body & body2, const Vector2D & anchor1, const Vector2D & anchor2 );
  Vector2D anchor1();
  void anchor1( const Vector2D & value );
  Vector2D anchor2();
  void anchor2( const Vector2D & value );
  double distance();
  void distance( double value );
};


}


#endif //FLATLAND_PIN_JOINT_H
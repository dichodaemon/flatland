#ifndef FLATLAND_GEAR_JOINT_H
#define FLATLAND_GEAR_JOINT_H


#include "Constraint.h"


namespace Flatland
{


class GearJoint : public Constraint
{
public:
  GearJoint( Body & body1, Body & body2, double ratio, double phase );
  double ratio() const;
  void ratio( double value );
  double phase() const;
  void phase( double value );
};


}


#endif //FLATLAND_GEAR_JOINT_H
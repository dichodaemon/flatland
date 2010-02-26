#include "GearJoint.h"

//------------------------------------------------------------------------------

Flatland::GearJoint::GearJoint(
  Body & body1,
  Body & body2,
  double ratio,
  double phase
)
{
  _constraint = cpGearJointNew( body1, body2, phase, ratio );
}

//------------------------------------------------------------------------------

double
Flatland::GearJoint::ratio() const
{
  return cpGearJointGetRatio( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::GearJoint::ratio( double value )
{
  cpGearJointSetRatio( _constraint, value );
}

//------------------------------------------------------------------------------

double
Flatland::GearJoint::phase() const
{
  return cpGearJointGetPhase( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::GearJoint::phase( double value )
{
  cpGearJointSetPhase( _constraint, value );
}

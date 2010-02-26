#include "PinJoint.h"

//------------------------------------------------------------------------------

Flatland::PinJoint::PinJoint( Body & body1, Body & body2, const Vector2D & anchor1, const Vector2D & anchor2 )
{
  _constraint = cpPinJointNew( body1, body2, anchor1, anchor2 );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::PinJoint::anchor1()
{
  return cpPinJointGetAnchr1( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::PinJoint::anchor1( const Vector2D & value )
{
  cpPinJointSetAnchr1( _constraint, value );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::PinJoint::anchor2()
{
  return cpPinJointGetAnchr2( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::PinJoint::anchor2( const Vector2D & value )
{
  cpPinJointSetAnchr2( _constraint, value );
}

//------------------------------------------------------------------------------

double
Flatland::PinJoint::distance()
{
  return cpPinJointGetDist( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::PinJoint::distance( double value )
{
  cpPinJointSetDist( _constraint, value );
}

//------------------------------------------------------------------------------


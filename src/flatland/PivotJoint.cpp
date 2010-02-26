#include "PivotJoint.h"

//------------------------------------------------------------------------------

Flatland::PivotJoint::PivotJoint(
  Body & body1,
  Body & body2,
  const Vector2D & pivot
)
{
  _constraint = cpPivotJointNew( body1, body2, pivot );
}

//------------------------------------------------------------------------------

Flatland::PivotJoint::PivotJoint(
  Body & body1,
  Body & body2,
  const Vector2D & anchor1,
  const Vector2D & anchor2
)
{
  _constraint = cpPivotJointNew2( body1, body2, anchor1, anchor2 );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::PivotJoint::anchor1()
{
  return cpPivotJointGetAnchr1( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::PivotJoint::anchor1( const Vector2D & value )
{
  cpPivotJointSetAnchr1( _constraint, value );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::PivotJoint::anchor2()
{
  return cpPivotJointGetAnchr2( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::PivotJoint::anchor2( const Vector2D & value )
{
  cpPivotJointSetAnchr2( _constraint, value );
}

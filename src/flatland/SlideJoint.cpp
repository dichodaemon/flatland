#include "SlideJoint.h"

//------------------------------------------------------------------------------

Flatland::SlideJoint::SlideJoint(
  Body & body1,
  Body & body2,
  const Vector2D & anchor1,
  const Vector2D & anchor2,
  double min,
  double max
)
{
  _constraint = cpSlideJointNew( body1, body2, anchor1, anchor2, min, max );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SlideJoint::anchor1()
{
  return cpSlideJointGetAnchr1( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::SlideJoint::anchor1( const Vector2D & value )
{
  cpSlideJointSetAnchr1( _constraint, value );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::SlideJoint::anchor2()
{
  return cpSlideJointGetAnchr2( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::SlideJoint::anchor2( const Vector2D & value )
{
  cpSlideJointSetAnchr2( _constraint, value );
}

//------------------------------------------------------------------------------

double
Flatland::SlideJoint::min() const
{
  return cpSlideJointGetMin( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::SlideJoint::min( double value )
{
  cpSlideJointSetMin( _constraint, value );
}

//------------------------------------------------------------------------------

double
Flatland::SlideJoint::max() const
{
  return cpSlideJointGetMax( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::SlideJoint::max( double value )
{
  cpSlideJointSetMax( _constraint, value );
}


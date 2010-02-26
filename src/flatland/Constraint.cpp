#include "Constraint.h"

//------------------------------------------------------------------------------

Flatland::Constraint::~Constraint()
{
  cpConstraintFree( _constraint );
}

//------------------------------------------------------------------------------

Flatland::Body
Flatland::Constraint::body1()
{
  return _constraint->a;
}

//------------------------------------------------------------------------------

Flatland::Body
Flatland::Constraint::body2()
{
  return _constraint->b;
}

//------------------------------------------------------------------------------

double
Flatland::Constraint::maxForce()
{
  return _constraint->maxForce;
}

//------------------------------------------------------------------------------

void
Flatland::Constraint::maxForce( double value )
{
  _constraint->maxForce = value;
}

//------------------------------------------------------------------------------

double
Flatland::Constraint::biasCoefficient()
{
  return _constraint->biasCoef;
}

//------------------------------------------------------------------------------

void
Flatland::Constraint::biasCoefficient( double value )
{
  _constraint->biasCoef = value;
}

//------------------------------------------------------------------------------

double
Flatland::Constraint::maxBias()
{
  return _constraint->maxBias;
}

//------------------------------------------------------------------------------

void
Flatland::Constraint::maxBias( double value )
{
  _constraint->maxBias = value;
}

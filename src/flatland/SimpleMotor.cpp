#include "SimpleMotor.h"

//------------------------------------------------------------------------------

Flatland::SimpleMotor::SimpleMotor( Body & body1, Body & body2, double rate )
{
  _constraint = cpSimpleMotorNew( body1, body2, rate );
}

//------------------------------------------------------------------------------

double
Flatland::SimpleMotor::rate() const
{
  return cpSimpleMotorGetRate( _constraint );
}

//------------------------------------------------------------------------------

void
Flatland::SimpleMotor::rate( double value )
{
  cpSimpleMotorSetRate( _constraint, value );
}

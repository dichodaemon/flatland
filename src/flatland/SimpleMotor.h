#ifndef FLATLAND_SIMPLE_MOTOR_H
#define FLATLAND_SIMPLE_MOTOR_H


#include "Constraint.h"


namespace Flatland
{


class SimpleMotor : public Constraint
{
public:
  SimpleMotor( Body & body1, Body & body2, double rate );
  double rate() const;
  void rate( double value );
};


}


#endif //FLATLAND_SIMPLE_MOTOR_H
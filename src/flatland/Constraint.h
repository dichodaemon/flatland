#ifndef FLATLAND_CONSTRAINT_H
#define FLATLAND_CONSTRAINT_H


#include "Body.h"
#include "ChipmunkObject.h"


namespace Flatland
{


class Constraint : public ChipmunkObject
{
public:
  virtual ~Constraint();
  Body body1();
  Body body2();
  double maxForce();
  void maxForce( double value );
  double biasCoefficient();
  void biasCoefficient( double value );
  double maxBias();
  void maxBias( double value );
protected:
  friend class Space;

  cpConstraint * _constraint;
};


}


#endif //FLATLAND_CONSTRAINT_H
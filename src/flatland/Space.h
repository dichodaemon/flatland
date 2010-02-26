#ifndef FLATLAND_SPACE_H
#define FLATLAND_SPACE_H


#include "ChipmunkObject.h"


namespace Flatland
{


class Body;
class Constraint;
class Shape;
class Vector2D;


class Space : public ChipmunkObject
{
public:
  Space();
  virtual ~Space();

  void iterations( int value );
  int iterations();
  
  void elasticIterations( int value );
  int elasticIterations();

  void damping( double value );
  double damping();

  void gravity( const Vector2D & g );

  void resizeStatic( float dim, int count );
  void resizeDynamic( float dim, int count );
  void rehashStatic();

  void addShape( Shape & shape );
  void addFixedShape( Shape & shape );
  void addBody( Body & body );
  void addConstraint( Constraint & constraint );

  void removeShape( Shape & shape );
  void removeFixedShape( Shape & shape );
  void removeBody( Body & body );
  void removeConstraint( Constraint & constraint );

  void step( double delta );
  
private:
  Space( const Space & );
  Space & operator=( const Space & );
  cpSpace * _space;
};


}


#endif //FLATLAND_SPACE_H
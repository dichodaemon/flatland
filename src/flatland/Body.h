#ifndef FLATLAND_BODY_H
#define FLATLAND_BODY_H


#include "Vector2D.h"
#include "ChipmunkObject.h"


namespace Flatland
{


class Body : public ChipmunkObject
{
public:
  Body( const Body & body );
  Body( double mass, double moment );
  Body(  cpBody * body );
  operator cpBody *() const;
  virtual ~Body();

  double mass();
  void mass( double value );
  
  double moment();
  void moment( double value );
  
  Vector2D position();
  void position( const Vector2D & value );

  Vector2D velocity();
  void velocity( const Vector2D & value );

  Vector2D force();
  void force( const Vector2D & value );


  double x() const;
  void x( double value );
  double y() const;
  void y( double value );
  double angle();
  void angle( double value );

  double angularVelocity();
  void angularVelocity( double value );

  double torque();
  void torque( double value );

  Vector2D rotation();

  void applyForce( const Vector2D & magnitude, const Vector2D & offset );
  void applyImpulse( const Vector2D & magnitude, const Vector2D & offset );
  void resetForces();
  

  Vector2D toWorld( const Vector2D & value );

  Vector2D toLocal( const Vector2D & value );

private:
  Body & operator=( const Body & );

  friend class Space;

  bool     _owner;
  cpBody * _body;
};


}


#endif //FLATLAND_BODY_H
#ifndef FLATLAND_VECTOR2D_H
#define FLATLAND_VECTOR2D_H


#include "ChipmunkObject.h"


namespace Flatland
{


class Vector2D : public ChipmunkObject
{
public:
  Vector2D();
  explicit Vector2D( double angle );
  Vector2D( const Vector2D & other );
  Vector2D( double x, double y );
  Vector2D( const cpVect & vector );
  Vector2D & operator=( const Vector2D & other );
  operator const cpVect &() const;

  double x() const;
  void x( double value );
  double y() const;
  void y( double value );

  Vector2D operator+( const Vector2D & other );
  Vector2D operator-( const Vector2D & other );
  Vector2D operator-();
  Vector2D operator*( double other );
  double dot( const Vector2D & other );
  double cross( const Vector2D & other );
  Vector2D ccwPerpendicular();
  Vector2D cwPerpendicular();
  Vector2D projection( const Vector2D & other );
  Vector2D ccwRotate( const Vector2D & other );
  Vector2D cwRotate( const Vector2D & other );
  double length();
  double length2();
  Vector2D lerp( const Vector2D & other, double t );
  Vector2D slerp( const Vector2D & other, double t );
  Vector2D clamp( double length );
  Vector2D normalize();
  double distance( const Vector2D & other );
  double distance2( const Vector2D & other );
  bool near( const Vector2D & other, double distance );
  double angle();
  
private:
  cpVect _vector;
  
};


}


#include "Vector2D-inline.h"


#endif //FLATLAND_VECTOR2D_H

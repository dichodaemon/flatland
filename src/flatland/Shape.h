#ifndef FLATLAND_SHAPE_H
#define FLATLAND_SHAPE_H


#include "BoundingBox.h"
#include "Body.h"
#include "Vector2D.h"
#include "ChipmunkObject.h"


namespace Flatland
{


class Shape : public ChipmunkObject
{
public:
  virtual ~Shape();

  bool contains( const Vector2D & vector );
  
  BoundingBox cacheBoundingBox();
  static void resedIdCounter();

  Body body() const;
 
  BoundingBox boundingBox();
  bool sensor();
  void sensor( bool value );
  double elasticity();
  void elasticity( double value );
  double friction();
  void friction( double value );
  Vector2D surfaceVelocity();
  void surfaceVelocity( const Vector2D & value );
  int collisionType();
  void collisionType( int value );
  int collisionGroup();
  void collisionGroup( int value );
  int layers();
  void layers( int value );

  bool fixed() const;

protected:
  friend class Space;
  Shape( cpShape * shape, bool fixed );
  
  cpShape * _shape;
  bool      _fixed;
};


}


#endif //FLATLAND_SHAPE_H
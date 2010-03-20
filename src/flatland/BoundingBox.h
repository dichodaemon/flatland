#ifndef FLATLAND_BOUNDING_BOX_H
#define FLATLAND_BOUNDING_BOX_H


#include "ChipmunkObject.h"
#include "Vector2D.h"


namespace Flatland
{


class BoundingBox
{
public:
  BoundingBox(
    double left = 0, 
    double top = 0, 
    double right = 0, 
    double bottom = 0 
  );
  BoundingBox( const cpBB & bb );
  operator const cpBB & () const;
  bool intersects( const BoundingBox & other ) const;
  bool contains( const BoundingBox & other ) const;
  bool contains( const Vector2D & other ) const;
  BoundingBox merge( const BoundingBox & other ) const;
  BoundingBox merge( const Vector2D & other ) const;
  Vector2D clamp( const Vector2D & other ) const;
  Vector2D wrap( const Vector2D & other ) const;
  
  double left() const;
  double top() const;
  double right() const;
  double bottom() const;

  void left( double value );
  void top( double value );
  void right( double value );
  void bottom( double value );
  
  
private:
  ChipmunkObject _chipmunk;
  cpBB           _bb;
};


}


#endif //FLATLAND_BOUNDING_BOX_H

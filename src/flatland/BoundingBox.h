#ifndef FLATLAND_BOUNDING_BOX_H
#define FLATLAND_BOUNDING_BOX_H


#include "ChipmunkObject.h"
#include "Vector2D.h"


namespace Flatland
{


class BoundingBox
{
public:
  BoundingBox( float x1, float y1, float x2, float y2 );
  BoundingBox( const cpBB & bb );
  operator const cpBB & () const;
  bool intersects( const BoundingBox & other ) const;
  bool contains( const BoundingBox & other ) const;
  bool contains( const Vector2D & other ) const;
  BoundingBox merge( const BoundingBox & other ) const;
  BoundingBox merge( const Vector2D & other ) const;
  Vector2D clamp( const Vector2D & other ) const;
  Vector2D wrap( const Vector2D & other ) const;
  
  
private:
  ChipmunkObject _chipmunk;
  cpBB           _bb;
};


}


#endif //FLATLAND_BOUNDING_BOX_H

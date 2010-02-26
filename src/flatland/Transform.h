#ifndef FLATLAND_TRANSFORM_H
#define FLATLAND_TRANSFORM_H


#include "Vector2D.h"


namespace Flatland
{


class Transform
{
public:
  Transform();
  
  void parent( const Transform & parent );
  const Transform & parent();
  
  void translation( const Vector2D & value );
  Vector2D translation();

  void scale( const Vector2D & value );
  Vector2D scale();

  void rotation( double value );
  double rotation();
  
  Vector2D toParent( const Vector2D & value );
  Vector2D fromParent( const Vector2D & value );

private:
  const Transform * _parent;
  Vector2D          _translation;
  Vector2D          _scale;
  double            _rotation;
};


}


#endif //FLATLAND_TRANSFORM_H

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
  
  Vector2D toParent( const Vector2D & value ) const;
  Vector2D fromParent( const Vector2D & value ) const;
  Vector2D toRoot( const Vector2D & value ) const;
  Vector2D fromRoot( const Vector2D & value ) const;

private:
  void update();

  const Transform * _parent;
  Vector2D          _translation;
  Vector2D          _scale;
  double            _rotation;

  double            _toM11;
  double            _toM12;
  double            _toM13;
  double            _toM21;
  double            _toM22;
  double            _toM23;

  double            _fromM11;
  double            _fromM12;
  double            _fromM13;
  double            _fromM21;
  double            _fromM22;
  double            _fromM23;
};


}


#endif //FLATLAND_TRANSFORM_H

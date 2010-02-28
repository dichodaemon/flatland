#include "Transform.h"
#include <cmath>

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::Transform::Transform()
  : _parent( NULL ),
    _translation( 0, 0 ),
    _scale( 1, 1 ),
    _rotation( 0 )
{
  update();
}

//------------------------------------------------------------------------------

void
Flatland::Transform::parent( const Transform & parent )
{
  _parent = &parent;
}

//------------------------------------------------------------------------------

const Flatland::Transform &
Flatland::Transform::parent()
{
  return *_parent;
}

//------------------------------------------------------------------------------

void
Flatland::Transform::translation( const Vector2D & value )
{
  _translation = value;
  update();
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::translation()
{
  return _translation;
}

//------------------------------------------------------------------------------

void
Flatland::Transform::scale( const Vector2D & value )
{
  _scale = value;
  update();
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::scale()
{
  return _scale;
}

//------------------------------------------------------------------------------

void
Flatland::Transform::rotation( double value )
{
  _rotation = value;
  update();
}

//------------------------------------------------------------------------------

double
Flatland::Transform::rotation()
{
  return _rotation;
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::toParent( const Vector2D & value ) const
{
  return Vector2D(
    value.x() * _toM11 + value.y() * _toM12 + _toM13,
    value.x() * _toM21 + value.y() * _toM22 + _toM23
  );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::fromParent( const Vector2D & value ) const
{
  return Vector2D(
    value.x() * _fromM11 + value.y() * _fromM12 + _fromM13,
    value.x() * _fromM21 + value.y() * _fromM22 + _fromM23
  );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::toRoot( const Vector2D & value ) const
{
  if ( _parent != NULL ) {
    return _parent->toRoot( toParent( value ) );
  }
  else {
    return toParent( value );
  }
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::fromRoot( const Vector2D & value ) const
{
  if ( _parent != NULL ) {
    return fromParent( _parent->fromRoot( value ) );
  }
  else {
    return fromParent( value );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Transform::update()
{
 double sx = _scale.x();
 double sy = _scale.y();
 double sx1 = 1.0 / _scale.x();
 double sy1 = 1.0 / _scale.y();
  //TODO: Use identities for negatives
 double cosmr = cos( -_rotation );
 double sinmr = sin( -_rotation );
 double cosr = cos( _rotation );
 double sinr = sin( _rotation );
  _fromM11 =  sx1 * cosmr;
  _fromM12 = -sx1 * sinmr;
  _fromM13 = -sx1 * ( _translation.x() * cosmr - _translation.y() * sinmr );
  _fromM21 =  sy1 * sinmr;
  _fromM22 =  sy1 * cosmr;
  _fromM23 = -sy1 * ( _translation.x() * sinmr + _translation.y() * cosmr );

  _toM11 =  sx * cosr;
  _toM12 = -sy * sinr;
  _toM13 = _translation.x();
  _toM21 =  sx * sinr;
  _toM22 =  sy * cosr;
  _toM23 = _translation.y();
}

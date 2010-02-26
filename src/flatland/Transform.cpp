#include "Transform.h"

//------------------------------------------------------------------------------

Flatland::Transform::Transform()
  : _parent( NULL )
{
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
}

//------------------------------------------------------------------------------

double
Flatland::Transform::rotation()
{
  return _rotation;
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::toParent( const Vector2D & value )
{
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Transform::fromParent( const Vector2D & value )
{
}

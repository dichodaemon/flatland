#include "Shape.h"

//------------------------------------------------------------------------------

Flatland::Shape::Shape( cpShape * shape, bool fixed )
  : _shape( shape ),
    _fixed( fixed )
{
  _shape->data = this;
}

//------------------------------------------------------------------------------

Flatland::Shape::~Shape()
{
  cpShapeFree( _shape );
}

//------------------------------------------------------------------------------

bool
Flatland::Shape::contains( const Vector2D & vector )
{
  return cpShapePointQuery( _shape, vector );
}

//------------------------------------------------------------------------------

Flatland::BoundingBox
Flatland::Shape::cacheBoundingBox()
{
  return cpShapeCacheBB( _shape );
}

//------------------------------------------------------------------------------

void
Flatland::Shape::resedIdCounter()
{
  cpResetShapeIdCounter();
}

//------------------------------------------------------------------------------

Flatland::Body
Flatland::Shape::body() const
{
  return _shape->body;
}

//------------------------------------------------------------------------------

Flatland::BoundingBox
Flatland::Shape::boundingBox()
{
  return _shape->bb;
}

//------------------------------------------------------------------------------

bool
Flatland::Shape::sensor()
{
  return _shape->sensor != 0;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::sensor( bool value )
{
  _shape->sensor = value;
}

//------------------------------------------------------------------------------

double
Flatland::Shape::elasticity()
{
  return _shape->e;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::elasticity( double value )
{
  _shape->e = value;
}

//------------------------------------------------------------------------------

double
Flatland::Shape::friction()
{
  return _shape->u;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::friction( double value )
{
  _shape->u = value;
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::Shape::surfaceVelocity()
{
  return _shape->surface_v;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::surfaceVelocity( const Vector2D & value )
{
  _shape->surface_v = value;
}

//------------------------------------------------------------------------------

int
Flatland::Shape::collisionType()
{
  return _shape->collision_type;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::collisionType( int value )
{
  _shape->collision_type = value;
}

//------------------------------------------------------------------------------

int
Flatland::Shape::collisionGroup()
{
  return _shape->group;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::collisionGroup( int value )
{
  _shape->group = value;
}

//------------------------------------------------------------------------------

int
Flatland::Shape::layers()
{
  return _shape->layers;
}

//------------------------------------------------------------------------------

void
Flatland::Shape::layers( int value )
{
  _shape->layers = value;
}

//------------------------------------------------------------------------------

bool
Flatland::Shape::fixed() const
{
  return _fixed;
}

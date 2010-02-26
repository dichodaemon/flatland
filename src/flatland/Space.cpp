#include "Space.h"
#include "Body.h"
#include "Constraint.h"
#include "Shape.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

Flatland::Space::Space()
{
  _space = cpSpaceNew();
}

//------------------------------------------------------------------------------

Flatland::Space::~Space()
{
  cpSpaceFree( _space );
}

//------------------------------------------------------------------------------

void
Flatland::Space::iterations( int value )
{
  _space->iterations = value;
}

//------------------------------------------------------------------------------

void
Flatland::Space::elasticIterations( int value )
{
  _space->elasticIterations = value;
}

//------------------------------------------------------------------------------

void
Flatland::Space::damping( double value )
{
  _space->damping = value;
}

//------------------------------------------------------------------------------

void
Flatland::Space::gravity( const Vector2D & g )
{
  _space->gravity = g;
}

//------------------------------------------------------------------------------

void
Flatland::Space::resizeStatic( float dim, int count )
{
  cpSpaceResizeStaticHash( _space, dim, count );
}

//------------------------------------------------------------------------------

void
Flatland::Space::resizeDynamic( float dim, int count )
{
  cpSpaceResizeActiveHash( _space, dim, count );
}

//------------------------------------------------------------------------------

void
Flatland::Space::rehashStatic()
{
  cpSpaceRehashStatic( _space );
}

//------------------------------------------------------------------------------

void
Flatland::Space::addShape( Shape & shape )
{
  cpSpaceAddShape( _space, shape._shape );
}

//------------------------------------------------------------------------------

void
Flatland::Space::addFixedShape( Shape & shape )
{
  cpSpaceAddStaticShape( _space, shape._shape );
}

//------------------------------------------------------------------------------

void
Flatland::Space::addBody( Body & body )
{
  cpSpaceAddBody( _space, body._body );
}

//------------------------------------------------------------------------------

void
Flatland::Space::addConstraint( Constraint & constraint )
{
  cpSpaceAddConstraint( _space, constraint._constraint );
}

//------------------------------------------------------------------------------

void
Flatland::Space::removeShape( Shape & shape )
{
  cpSpaceRemoveShape( _space, shape._shape );
}

//------------------------------------------------------------------------------

void
Flatland::Space::removeFixedShape( Shape & shape )
{
  cpSpaceRemoveStaticShape( _space, shape._shape );
}

//------------------------------------------------------------------------------

void
Flatland::Space::removeBody( Body & body )
{
  cpSpaceRemoveBody( _space, body._body );
}

//------------------------------------------------------------------------------

void
Flatland::Space::removeConstraint( Constraint & constraint )
{
  cpSpaceRemoveConstraint( _space, constraint._constraint );
}

//------------------------------------------------------------------------------

void
Flatland::Space::step( double delta )
{
  cpSpaceStep( _space, delta );
}

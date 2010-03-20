#include "BoundingBox.h"

//------------------------------------------------------------------------------

Flatland::BoundingBox::BoundingBox( 
  double left, 
  double top, 
  double right, 
  double bottom 
)
{
  _bb.l = left;
  _bb.t = top;
  _bb.r = right;
  _bb.b = bottom;
}

//------------------------------------------------------------------------------

Flatland::BoundingBox::BoundingBox( const cpBB & bb )
{
  _bb = bb;
}

//------------------------------------------------------------------------------

Flatland::BoundingBox::operator const cpBB & () const
{
  return _bb;
}

//------------------------------------------------------------------------------

bool
Flatland::BoundingBox::intersects( const BoundingBox & other ) const
{
  return cpBBintersects( _bb, other );
}

//------------------------------------------------------------------------------

bool
Flatland::BoundingBox::contains( const BoundingBox & other ) const
{
  return cpBBcontainsBB( _bb, other );
}

//------------------------------------------------------------------------------

bool
Flatland::BoundingBox::contains( const Vector2D & other ) const
{
  return cpBBcontainsVect( _bb, other );
}

//------------------------------------------------------------------------------

Flatland::BoundingBox
Flatland::BoundingBox::merge( const BoundingBox & other ) const
{
  return cpBBmerge( _bb, other );
}

//------------------------------------------------------------------------------

Flatland::BoundingBox
Flatland::BoundingBox::merge( const Vector2D & other ) const
{
  return cpBBexpand( _bb, other );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::BoundingBox::clamp( const Vector2D & other ) const
{
  return cpBBClampVect( _bb, other );
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::BoundingBox::wrap( const Vector2D & other ) const
{
  return cpBBWrapVect( _bb, other );
}

//------------------------------------------------------------------------------

double
Flatland::BoundingBox::left() const
{
  return _bb.l;
}

//------------------------------------------------------------------------------

double
Flatland::BoundingBox::top() const
{
  return _bb.t;
}

//------------------------------------------------------------------------------

double
Flatland::BoundingBox::right() const
{
  return _bb.r;
}

//------------------------------------------------------------------------------

double
Flatland::BoundingBox::bottom() const
{
  return _bb.b;
}

//------------------------------------------------------------------------------

void
Flatland::BoundingBox::left( double value )
{
  _bb.l = value;
}

//------------------------------------------------------------------------------

void
Flatland::BoundingBox::top( double value )
{
  _bb.t = value;
}

//------------------------------------------------------------------------------

void
Flatland::BoundingBox::right( double value )
{
  _bb.r = value;
}

//------------------------------------------------------------------------------

void
Flatland::BoundingBox::bottom( double value )
{
  _bb.b = value;
}

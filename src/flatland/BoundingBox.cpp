#include "BoundingBox.h"

//------------------------------------------------------------------------------

Flatland::BoundingBox::BoundingBox( float x1, float y1, float x2, float y2 )
{
  _bb.l = x1;
  _bb.t = y1;
  _bb.r = x2;
  _bb.b = y2;
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



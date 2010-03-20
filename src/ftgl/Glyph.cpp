#include "Glyph.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Glyph::Glyph()
{
}

//------------------------------------------------------------------------------

Glyph::~Glyph()
{ 
}

//------------------------------------------------------------------------------

const BoundingBox & 
Glyph::bounds() const
{
  return _bb; 
}

//------------------------------------------------------------------------------

BoundingBox & 
Glyph::bounds()
{
  return _bb;
}

//------------------------------------------------------------------------------

const BoundingBox & 
Glyph::textureCoordinates() const
{
  return _textureCoordinates; 
}

//------------------------------------------------------------------------------

BoundingBox & 
Glyph::textureCoordinates()
{
  return _textureCoordinates;
}

//------------------------------------------------------------------------------

int 
Glyph::skip() const
{
  return _skip;
}

//------------------------------------------------------------------------------

void 
Glyph::skip( int value )
{
  _skip = value;
}

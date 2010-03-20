#include "Image.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Image::Image()
  : _impl( newImage() )
{
}

//------------------------------------------------------------------------------

Image::Image( const std::string & filename )
  : _impl( newImageFromFile( filename ) )
{
}

//------------------------------------------------------------------------------

Image::~Image()
{  
  delete _impl;
}

//------------------------------------------------------------------------------

const ImageBase *
Image::implementation() const
{
  return _impl;
}

//------------------------------------------------------------------------------

void 
Image::fromBuffer( const uint8_t * buffer, size_t size )
{
  _impl->fromBuffer( buffer, size );
}


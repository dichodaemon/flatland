#include "Image.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Image::Image( const std::string & filename )
  : _impl( newImage( filename ) )
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

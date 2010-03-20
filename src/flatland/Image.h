#ifndef FLATLAND_IMAGE_H
#define FLATLAND_IMAGE_H


#include "ImageBase.h"
#include <string>


namespace Flatland
{
 
 
class Image : public ImageBase
{
public:
  Image();
  Image( const std::string & filename );
  virtual ~Image();
  void fromBuffer( const uint8_t * buffer, size_t size );
  const ImageBase * implementation() const;

private:
  ImageBase * _impl;
}; 
 
}

#endif //FLATLAND_IMAGE_H

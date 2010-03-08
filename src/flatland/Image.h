#ifndef FLATLAND_IMAGE_H
#define FLATLAND_IMAGE_H


#include "ImageBase.h"
#include <string>


namespace Flatland
{
 
 
class Image : public ImageBase
{
public:
  Image( const std::string & filename );
  virtual ~Image();
  const ImageBase * implementation() const;

private:
  ImageBase * _impl;
}; 
 
}

#endif //FLATLAND_IMAGE_H

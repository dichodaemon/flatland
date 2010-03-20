#ifndef FLATLAND_IMAGE_BASE_H
#define FLATLAND_IMAGE_BASE_H


#include <string>


namespace Flatland
{
 
 
class ImageBase
{
public:
  virtual ~ImageBase();
  virtual void fromBuffer( const uint8_t * buffer, size_t size ) = 0;
}; 

 
}


extern "C"
{
  Flatland::ImageBase * newImage();
  Flatland::ImageBase * newImageFromFile( const std::string & filename );
}


#endif //FLATLAND_IMAGE_BASE_H

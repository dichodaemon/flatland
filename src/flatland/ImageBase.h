#ifndef FLATLAND_IMAGE_BASE_H
#define FLATLAND_IMAGE_BASE_H


#include <string>


namespace Flatland
{
 
 
class ImageBase
{
public:
  virtual ~ImageBase();
}; 

 
}


extern "C"
{
  Flatland::ImageBase * newImage( const std::string & filename );
}


#endif //FLATLAND_IMAGE_BASE_H

#ifndef IMAGE_H
#define IMAGE_H


#include <flatland/ImageBase.h>
#include <string>


class GraphicsContext;

class Image : public Flatland::ImageBase
{
public:
  Image();
  Image( const std::string & filename );  
  void fromBuffer( const uint8_t * buffer, size_t size );
  virtual ~Image();
  
  int index() const;

private:
  friend class ::GraphicsContext;
  uint32_t _image;
}; 
 
#endif //IMAGE_H

#ifndef IMAGE_H
#define IMAGE_H


#include <flatland/ImageBase.h>
#include <string>


class GraphicsContext;

class Image : public Flatland::ImageBase
{
public:
  Image( const std::string & filename );
  virtual ~Image();
  
  int index() const;

private:
  friend class ::GraphicsContext;
  int _image;
}; 
 
#endif //IMAGE_H

#ifndef FLATLAND_GRAPHICS_CONTEXT_H
#define FLATLAND_GRAPHICS_CONTEXT_H


#include "GraphicsContextBase.h"
#include <cstdlib>


namespace Flatland
{


class Window;
  

class GraphicsContext : public GraphicsContextBase
{
public:

  GraphicsContext( size_t width, size_t height );
  
  GraphicsContext( Window & screen );
  
  virtual ~GraphicsContext();

  Vector2D toGraphics( const Vector2D & vector );
  Vector2D toWorld( const Vector2D & vector );

  void setTransform( const Vector2D & center, double rotation, double width );
  
  double width();
  double height();

  void drawCircle(
    double x,
    double y,
    double radius,
    const Color & color,
    size_t thickness = 1
  );
  
  void drawCircle(
    double x,
    double y,
    double radius,
    const Color & color,
    size_t thickness,
    bool imageCoordinates
  );
  
  void fillCircle(
    double x,
    double y,
    double radius,
    const Color & color
  );
  
  void fillCircle(
    double x,
    double y,
    double radius,
    const Color & color,
    bool imageCoordinates
  );

  void drawLine(
    double x1,
    double y1,
    double x2,
    double y2,
    const Color & color,
    size_t thickness = 1
  );
  
  void drawLine(
    double x1,
    double y1,
    double x2,
    double y2,
    const Color & color,
    size_t thickness,
    bool imageCoordinates
  );
  
  void drawImage( 
    const Image & image, 
    const Transform & transform, 
    double width, 
    double height 
  );

  void clear( const Color & color );

private:
  friend class Window;
  GraphicsContextBase * _impl;
};


}


#endif //FLATLAND_GRAPHICS_CONTEXT_H

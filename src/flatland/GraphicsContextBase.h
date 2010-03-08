#ifndef FLATLAND_GRAPHICS_CONTEXT_BASE_H
#define FLATLAND_GRAPHICS_CONTEXT_BASE_H


#include "Transform.h"
#include "Vector2D.h"
#include <cstdlib>


namespace Flatland
{


class Color;
class Image;
class Transform;
class WindowBase;


class GraphicsContextBase
{
public:
  typedef GraphicsContextBase * (*Factory)( size_t width, size_t height );
  typedef GraphicsContextBase * (*WindowFactory)( WindowBase & );
  virtual ~GraphicsContextBase();

  Vector2D toGraphics( const Vector2D & vector );
  Vector2D toWorld( const Vector2D & vector );

  void setTransform( const Vector2D & center, double rotation, double width );
  
  virtual double width() = 0;
  virtual double height() = 0;

  virtual void drawCircle(
    double x,
    double y,
    double radius,
    const Color & color,
    size_t thickness
  ) = 0;

  virtual void fillCircle(
    double x,
    double y,
    double radius,
    const Color & color
  ) = 0;

  virtual void drawLine(
    double x1,
    double y1,
    double x2,
    double y2,
    const Color & color,
    size_t thickness
  ) = 0;
  
  virtual void drawImage( 
    const Image & image, 
    const Transform & transform, 
    double width, 
    double height 
    ) = 0;

  virtual void clear( const Color & color ) = 0;

protected:
  Transform _transform;  
  
private:
  friend class Window;
};


}

extern "C"
{
  Flatland::GraphicsContextBase * 
  newGraphicsContext( size_t width, size_t height );

  Flatland::GraphicsContextBase * 
  newGraphicsContextFromWindow( Flatland::WindowBase & window );
}

#endif //FLATLAND_GRAPHICS_CONTEXT_BASE_H

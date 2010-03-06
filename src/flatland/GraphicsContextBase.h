#ifndef FLATLAND_GRAPHICS_CONTEXT_BASE_H
#define FLATLAND_GRAPHICS_CONTEXT_BASE_H


#include <cstdlib>


namespace Flatland
{


class Color;
class WindowBase;


class GraphicsContextBase
{
public:
  typedef GraphicsContextBase * (*Factory)( size_t width, size_t height );
  typedef GraphicsContextBase * (*WindowFactory)( WindowBase & );
  virtual ~GraphicsContextBase();

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

  virtual void clear( const Color & color ) = 0;

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

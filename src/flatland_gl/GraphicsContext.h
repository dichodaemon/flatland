#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H


// #include <FTGL/ftgl.h>
#include <flatland/GraphicsContextBase.h>


namespace Flatland
{
  class Color;
  class WindowBase;
}


class GraphicsContext : public Flatland::GraphicsContextBase
{
public:
  GraphicsContext( size_t width, size_t height );
  GraphicsContext( Flatland::WindowBase & screen );
  virtual ~GraphicsContext();

  double width();
  double height();

  void drawCircle(
    double x,
    double y,
    double radius,
    const Flatland::Color & color,
    size_t thickness
  );

  void fillCircle(
    double x,
    double y,
    double radius,
    const Flatland::Color & color
  );

  void drawLine(
    double x1,
    double y1,
    double x2,
    double y2,
    const Flatland::Color & color,
    size_t thickness
  );

  void clear( const Flatland::Color & color );

private:
  bool          _owner;
  double        _width;
  double        _height;

};


#endif //GRAPHICS_CONTEXT_H

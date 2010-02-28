#ifndef FLATLAND_GRAPHICS_CONTEXT_H
#define FLATLAND_GRAPHICS_CONTEXT_H


#include "GraphicsContextBase.h"
#include "Transform.h"
#include "Vector2D.h"
#include <cstdlib>


namespace Flatland
{


class Color;
class ScreenBase;
class Screen;


class GraphicsContext : public GraphicsContextBase
{
public:

  GraphicsContext( size_t width, size_t height );
  
  GraphicsContext( Screen & screen );
  
  virtual ~GraphicsContext();

  double width();
  double height();

  void setTransform( const Vector2D & center, double rotation, double width );
  Vector2D toGraphics( const Vector2D & vector );
  Vector2D toWorld( const Vector2D & vector );

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

  void clear( const Color & color );

private:
  friend class Screen;
  GraphicsContextBase * _impl;
  Transform             _transform;
};


}


#endif //FLATLAND_GRAPHICS_CONTEXT_H

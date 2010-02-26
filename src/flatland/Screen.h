#ifndef FLATLAND_SCREEN_H
#define FLATLAND_SCREEN_H


#include "ScreenBase.h"
#include <cstdlib>


namespace Flatland
{


class GraphicsContextBase;


class Screen : public ScreenBase
{
public:
  Screen( size_t width, size_t height );
  virtual ~Screen();
  void flip();
  void display( GraphicsContextBase & graphics );
  double width();
  double height();
private:
  friend class GraphicsContext;
  ScreenBase * _impl;
};


}


#endif //FLATLAND_SCREEN_H

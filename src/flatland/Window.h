#ifndef FLATLAND_WINDOW_H
#define FLATLAND_WINDOW_H


#include "WindowBase.h"
#include <cstdlib>


namespace Flatland
{


class Bus;
class GraphicsContextBase;


class Window : public WindowBase
{
public:
  Window( Bus & bus, size_t width, size_t height );
  virtual ~Window();
  void flip();
  void display( GraphicsContextBase & graphics );
  double width();
  double height();
  void run( double frequency );
private:
  friend class GraphicsContext;
  WindowBase * _impl;
};


}


#endif //FLATLAND_WINDOW_H

#ifndef FLATLAND_WINDOW_BASE_H
#define FLATLAND_WINDOW_BASE_H


#include <cstdlib>


namespace Flatland
{


class Bus;
class GraphicsContextBase;


class WindowBase
{
public:
  typedef  WindowBase * (*Factory)( Bus &, size_t, size_t );
  virtual ~WindowBase();
  virtual void flip() = 0;
  virtual void display( GraphicsContextBase & graphics ) = 0;
  virtual double width()  = 0;
  virtual double height() = 0;
  virtual void run( double frequency ) = 0;

protected:
  friend class GraphicsContextBase;
};


}

extern "C"
{
  Flatland::WindowBase * 
  newWindow( Flatland::Bus & bus, size_t width, size_t height );
}

#endif //FLATLAND_WINDOW_BASE_H

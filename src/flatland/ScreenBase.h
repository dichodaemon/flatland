#ifndef FLATLAND_SCREEN_BASE_H
#define FLATLAND_SCREEN_BASE_H


#include <cstdlib>


namespace Flatland
{


class GraphicsContextBase;


class ScreenBase
{
public:
  typedef  ScreenBase * (*Factory)( size_t, size_t );
  virtual ~ScreenBase();
  virtual void flip() = 0;
  virtual void display( GraphicsContextBase & graphics ) = 0;
  virtual double width()  = 0;
  virtual double height() = 0;
protected:
  friend class GraphicsContextBase;
};


}


#endif //FLATLAND_SCREEN_BASE_H

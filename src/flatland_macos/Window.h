#ifndef WINDOW_H
#define WINDOW_H


#import "ApplicationDelegate.h"
#import <Cocoa/Cocoa.h>
#include <flatland/Bus.h>
#include <flatland/WindowBase.h>


namespace Flatland
{
  class GraphicsContextBase;
}


class Window : public Flatland::WindowBase
{
public:
  Window( Flatland::Bus & bus, size_t width, size_t height );
  double width();
  double height();
  void flip();
  void display( Flatland::GraphicsContextBase & graphics );
  void run( double frequency );
private:
  Flatland::Bus &       _bus;
  double                _width;
  double                _height;
  ApplicationDelegate * _delegate;
};

#endif //WINDOW_H

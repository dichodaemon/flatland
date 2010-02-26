#ifndef SCREEN_H
#define SCREEN_H


#include "SDLObject.h"
#include <flatland/ScreenBase.h>


namespace Flatland
{
  class GraphicsContextBase;
}


class Screen : public Flatland::ScreenBase
{
public:
  Screen( size_t width, size_t height );
  double width();
  double height();
  void flip();
  void display( Flatland::GraphicsContextBase & graphics );

private:
  friend class GraphicsContext;
  SDLObject     _sdl;
  SDL_Surface * _surface;
};

extern "C"
{
  Flatland::ScreenBase * newScreen( size_t width, size_t height );
}

#endif //SCREEN_H

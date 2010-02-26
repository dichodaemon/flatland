#ifndef SDL_OBJECT_H
#define SDL_OBJECT_H


extern "C" {
  #include <SDL/SDL.h>
  #include <SDL/SDL_opengl.h>
}
#include <cstdlib>


class SDLObject
{
public:
  SDLObject();
  virtual ~SDLObject();
private:
  static size_t _references;
};


#endif //SDL_OBJECT_H

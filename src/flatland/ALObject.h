#ifndef FLATLAND_AL_OBJECT_H
#define FLATLAND_AL_OBJECT_H

#if defined (__APPLE__)
  #include <OpenAL/al.h>
  #include <OpenAL/alc.h>
#else
  #include <AL/al.h>
  #include <AL/alc.h>
#endif
#include <cstdlib>


namespace Flatland
{
  

class ALObject
{
public:
  ALObject();
  virtual ~ALObject();
private:
  static size_t _references;
  ALCcontext *  _context;
  ALCdevice *   _device;
};


}


#endif //FLATLAND_AL_OBJECT_H

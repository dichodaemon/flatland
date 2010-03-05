#ifndef FLATLAND_SOUND_BUFFER_H
#define FLATLAND_SOUND_BUFFER_H


#include "ALObject.h"
#include <string>


namespace Flatland
{


class SoundBuffer
{
public:
  SoundBuffer( const std::string & filename );
  virtual ~SoundBuffer();
  
  int frequency();
  int size();
  int bitsPerSample();
  int channels();
  
private:
  ALObject _al;
  ALuint   _buffer;
}; 


}


#endif //FLATLAND_SOUND_BUFFER_H

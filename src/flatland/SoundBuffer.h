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
  
  operator int() const;
  
  int frequency() const;
  int size() const ;
  int bitsPerSample() const;
  int channels() const;
  
private:
  ALObject _al;
  ALuint   _buffer;
}; 


}


#endif //FLATLAND_SOUND_BUFFER_H

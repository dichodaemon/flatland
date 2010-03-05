#ifndef FLATLAND_SOUND_SOURCE_H
#define FLATLAND_SOUND_SOURCE_H


#include "ALObject.h"
#include <flatland/Vector2D.h>


namespace Flatland
{


class SoundSource
{
public:
  SoundSource();
  virtual ~SoundSource();
  
  void position( const Vector2D & value );
  Vector2D position();
  
  void velocity( const Vector2D & value );
  Vector2D velocity();
  
  void pitch( double value );
  double pitch();
  
  void gain( double value );
  double gain();
  
  void loop( bool value );
  bool loop();
  
  void play();
  void stop();
  void pause();
  
private:
  ALObject _al;
  ALuint   _source;
}; 


}


#endif //FLATLAND_SOUND_SOURCE_H

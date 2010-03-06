#ifndef FLATLAND_SOUND_SOURCE_H
#define FLATLAND_SOUND_SOURCE_H


#include "ALObject.h"
#include "Vector2D.h"


namespace Flatland
{


class SoundBuffer;


class SoundSource
{
public:
  SoundSource();
  virtual ~SoundSource();
  
  void position( const Vector2D & value );
  Vector2D position() const;
  
  void velocity( const Vector2D & value );
  Vector2D velocity() const;
  
  void pitch( double value );
  double pitch() const;
  
  void gain( double value );
  double gain() const;
  
  void loop( bool value );
  bool loop() const;
  
  void buffer( const SoundBuffer & value );
  
  void play();
  void stop();
  void pause();
  
private:
  ALObject _al;
  ALuint   _source;
}; 


}


#endif //FLATLAND_SOUND_SOURCE_H

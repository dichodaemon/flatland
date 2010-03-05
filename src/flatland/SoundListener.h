#ifndef FLATLAND_SOUND_LISTENER_H
#define FLATLAND_SOUND_LISTENER_H


#include "ALObject.h"
#include <flatland/Vector2D.h>


namespace Flatland
{


class SoundListener
{
public:
  SoundListener();
  virtual ~SoundListener();
  
  void position( const Vector2D & value );
  Vector2D position();
  
  void velocity( const Vector2D & value );
  Vector2D velocity();

  void orientation( double angle );
  double orientation();
  
  void gain( double value );
  double gain();

private:
  ALObject _al;
}; 


}


#endif //FLATLAND_SOUND_LISTENER_H

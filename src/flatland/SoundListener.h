#ifndef FLATLAND_SOUND_LISTENER_H
#define FLATLAND_SOUND_LISTENER_H


#include "ALObject.h"
#include "Vector2D.h"


namespace Flatland
{


class SoundListener
{
public:
  SoundListener();
  virtual ~SoundListener();
  
  void position( const Vector2D & value );
  Vector2D position() const;
  
  void velocity( const Vector2D & value );
  Vector2D velocity() const;

  void orientation( double angle );
  double orientation() const;
  
  void gain( double value );
  double gain() const;

private:
  ALObject _al;
}; 


}


#endif //FLATLAND_SOUND_LISTENER_H

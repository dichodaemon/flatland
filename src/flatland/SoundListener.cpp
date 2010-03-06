#include "SoundListener.h"

using namespace Flatland;

//------------------------------------------------------------------------------

SoundListener::SoundListener()
{
}

//------------------------------------------------------------------------------

SoundListener::~SoundListener()
{
}

//------------------------------------------------------------------------------

void 
SoundListener::position( const Vector2D & value )
{
  ALfloat v[] = { value.x(), value.y(), 0.0 }; 
  alListenerfv( AL_POSITION, v ); 
}

//------------------------------------------------------------------------------

Vector2D 
SoundListener::position() const
{
  ALfloat v[] = { 0.0, 0.0, 0.0 }; 
  alGetListenerfv( AL_POSITION, v ); 
  return Vector2D( v[0], v[1] );
}

//------------------------------------------------------------------------------

void 
SoundListener::velocity( const Vector2D & value )
{
  ALfloat v[] = { value.x(), value.y(), 0.0 }; 
  alListenerfv( AL_VELOCITY, v ); 
}

//------------------------------------------------------------------------------

Vector2D 
SoundListener::velocity() const
{
  ALfloat v[] = { 0.0, 0.0, 0.0 }; 
  alGetListenerfv( AL_VELOCITY, v ); 
  return Vector2D( v[0], v[1] );
}

//------------------------------------------------------------------------------

void 
SoundListener::orientation( double value )
{
  // alListenerf( AL_GAIN, value ); 
}

//------------------------------------------------------------------------------

double 
SoundListener::orientation() const
{
  // double result;
  // alGetListenerf( AL_GAIN, &result );
  // return result;
}

//------------------------------------------------------------------------------

void 
SoundListener::gain( double value )
{
  alListenerf( AL_GAIN, value ); 
}

//------------------------------------------------------------------------------

double 
SoundListener::gain() const
{
  ALfloat result;
  alGetListenerf( AL_GAIN, &result );
  return result;
}


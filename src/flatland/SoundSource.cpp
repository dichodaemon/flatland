#include "SoundSource.h"

using namespace Flatland;

//------------------------------------------------------------------------------

SoundSource::SoundSource()
{
  alGenSources( 1, &_source );
}

//------------------------------------------------------------------------------

SoundSource::~SoundSource()
{
  alDeleteSources( 1, &_source );
}

//------------------------------------------------------------------------------

void 
SoundSource::position( const Vector2D & value )
{
  ALfloat v[] = { value.x(), value.y(), 0.0 }; 
  alSourcefv( _source, AL_POSITION, v ); 
}

//------------------------------------------------------------------------------

Vector2D 
SoundSource::position()
{
  ALfloat v[] = { 0.0, 0.0, 0.0 }; 
  alGetSourcefv( _source, AL_POSITION, v ); 
  return Vector2D( v[0], v[1] );
}

//------------------------------------------------------------------------------

void 
SoundSource::velocity( const Vector2D & value )
{
  ALfloat v[] = { value.x(), value.y(), 0.0 }; 
  alSourcefv( _source, AL_VELOCITY, v ); 
}

//------------------------------------------------------------------------------

Vector2D 
SoundSource::velocity()
{
  ALfloat v[] = { 0.0, 0.0, 0.0 }; 
  alGetSourcefv( _source, AL_VELOCITY, v ); 
  return Vector2D( v[0], v[1] );
}

//------------------------------------------------------------------------------

void 
SoundSource::pitch( double value )
{
  alSourcef( _source, AL_PITCH, value ); 
}

//------------------------------------------------------------------------------

double 
SoundSource::pitch()
{
  ALfloat result;
  alGetSourcef( _source, AL_PITCH, &result );
  return result;
}

//------------------------------------------------------------------------------

void 
SoundSource::gain( double value )
{
  alSourcef( _source, AL_GAIN, value ); 
}

//------------------------------------------------------------------------------

double 
SoundSource::gain()
{
  ALfloat result;
  alGetSourcef( _source, AL_GAIN, &result );
  return result;
}

//------------------------------------------------------------------------------

void 
SoundSource::loop( bool value )
{
  alSourcei( _source, AL_LOOPING, value ); 
}

//------------------------------------------------------------------------------

bool 
SoundSource::loop()
{
  int result;
  alGetSourcei( _source, AL_LOOPING, &result );
  return result;
}

//------------------------------------------------------------------------------

void 
SoundSource::play()
{
  alSourcePlay( _source );
}

//------------------------------------------------------------------------------

void 
SoundSource::stop()
{
  alSourceStop( _source );
}

//------------------------------------------------------------------------------

void 
SoundSource::pause()
{
  alSourcePause( _source );
}

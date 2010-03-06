#include "ALObject.h"
#include "Logger.h"

using namespace Flatland;

//------------------------------------------------------------------------------

size_t ALObject::_references = 0;

//------------------------------------------------------------------------------

ALObject::ALObject()
{
  if ( _references == 0 ) {
    Logger::info( "Initializing OpenAL", "OpenAL" );
  	_device = alcOpenDevice( NULL );
  	if ( _device ) {
  		_context = alcCreateContext( _device, NULL );
  		alcMakeContextCurrent( _context );
  	} else {
      Logger::error( "Unable to open device", "OpenAL" );
  	}
  }
  _references++;
}

//------------------------------------------------------------------------------

ALObject::~ALObject()
{
  _references--;
  if ( _references == 0 ) {
    Logger::info( "Terminating OpenAL", "OpenAL" );
    alcDestroyContext( _context );
    alcCloseDevice( _device );
  }
}
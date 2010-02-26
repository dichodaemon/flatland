#include "SDLObject.h"
#include <flatland/Logger.h>

using namespace Flatland;

//------------------------------------------------------------------------------

size_t SDLObject::_references = 0;

//------------------------------------------------------------------------------

SDLObject::SDLObject()
{
  if ( _references == 0 ) {
    Logger::info( "Initializing SDL", "SDL" );
    SDL_Init( SDL_INIT_EVERYTHING );
  }
  _references++;
}

//------------------------------------------------------------------------------

SDLObject::~SDLObject()
{
  _references--;
  if ( _references == 0 ) {
    Logger::info( "Quitting SDL", "SDL" );
    SDL_Quit();
  }
}
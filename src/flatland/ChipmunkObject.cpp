#include "ChipmunkObject.h"
#include "Logger.h"

using namespace Flatland;

//------------------------------------------------------------------------------

size_t ChipmunkObject::_references = 0;

//------------------------------------------------------------------------------

ChipmunkObject::ChipmunkObject()
{
  if ( _references == 0 ) {
    Logger::info( "Initializing Chipmunk", "Chipmunk" );
    cpInitChipmunk();
  }
  _references++;
}

//------------------------------------------------------------------------------
ChipmunkObject::~ChipmunkObject()
{
  _references--;
  if ( _references == 0 ) {
    Logger::info( "Quitting Chipmunk", "Chipmunk" );
  }
}
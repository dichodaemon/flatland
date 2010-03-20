#include "FreeTypeObject.h"
#include <flatland/Logger.h>

using Flatland::Logger;

//------------------------------------------------------------------------------

size_t FreeTypeObject::_references = 0;
FT_Library _library;

//------------------------------------------------------------------------------

FreeTypeObject::FreeTypeObject()
{
  if ( _references == 0 ) {
    Logger::info( "Initializing Freetype", "FreeType" );
    FT_Init_FreeType( &_library );
  }

  _references++;
}

//------------------------------------------------------------------------------

FreeTypeObject::~FreeTypeObject()
{
  _references--;

  if ( _references == 0 ) {
    Logger::info( "Terminating Freetype", "FreeType" );
    FT_Done_FreeType( _library );
  }
}

//------------------------------------------------------------------------------

FT_Library &
FreeTypeObject::library()
{
  return _library;
}
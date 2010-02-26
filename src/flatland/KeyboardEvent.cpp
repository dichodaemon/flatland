#include "KeyboardEvent.h"

//------------------------------------------------------------------------------

Flatland::KeyboardEvent::KeyboardEvent( Keys key )
  : _key( key )
{
}

//------------------------------------------------------------------------------

Flatland::KeyboardEvent::Keys
Flatland::KeyboardEvent::key() const
{
  return _key;
}

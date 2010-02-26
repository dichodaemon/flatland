#include "MouseEvent.h"

//------------------------------------------------------------------------------

Flatland::MouseEvent::MouseEvent( int x, int y )
  : _x( x ),
    _y( y )
{
}

//------------------------------------------------------------------------------

int
Flatland::MouseEvent::x() const
{
  return _x;
}

//------------------------------------------------------------------------------

int
Flatland::MouseEvent::y() const
{
  return _y;
}

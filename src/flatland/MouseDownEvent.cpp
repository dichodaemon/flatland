#include "MouseDownEvent.h"

//------------------------------------------------------------------------------

Flatland::MouseDownEvent::MouseDownEvent( int x, int y, Button button )
  : MouseEvent( x, y ),
    _button( button )
{
}

//------------------------------------------------------------------------------


Flatland::MouseEvent::Button
Flatland::MouseDownEvent::button() const
{
  return _button;
}

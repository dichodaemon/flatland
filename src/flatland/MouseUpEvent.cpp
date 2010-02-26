#include "MouseUpEvent.h"

//------------------------------------------------------------------------------

Flatland::MouseUpEvent::MouseUpEvent( int x, int y, Button button )
  : MouseEvent( x, y ),
    _button( button )
{
}

//------------------------------------------------------------------------------


Flatland::MouseEvent::Button
Flatland::MouseUpEvent::button() const
{
  return _button;
}

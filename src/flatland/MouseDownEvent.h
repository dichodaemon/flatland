#ifndef FLATLAND_MOUSE_DOWN_EVENT_H
#define FLATLAND_MOUSE_DOWN_EVENT_H


#include "MouseEvent.h"


namespace Flatland
{


class MouseDownEvent : public MouseEvent
{
public:
  MouseDownEvent( int x, int y, Button button );
  Button button() const;
  
private:
  Button _button;
};


}


#endif //FLATLAND_MOUSE_DOWN_EVENT_H

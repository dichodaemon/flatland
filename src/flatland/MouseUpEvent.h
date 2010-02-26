#ifndef FLATLAND_MOUSE_UP_EVENT_H
#define FLATLAND_MOUSE_UP_EVENT_H


#include "MouseEvent.h"


namespace Flatland
{


class MouseUpEvent : public MouseEvent
{
public:
  MouseUpEvent( int x, int y, Button button );
  Button button() const;

private:
  Button _button;
};


}


#endif //FLATLAND_MOUSE_UP_EVENT_H

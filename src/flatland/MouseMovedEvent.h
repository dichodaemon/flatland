#ifndef FLATLAND_MOUSE_MOVED_EVENT_H
#define FLATLAND_MOUSE_MOVED_EVENT_H


#include "MouseEvent.h"


namespace Flatland
{

class MouseMovedEvent : public MouseEvent
{
public:
  MouseMovedEvent( int x, int y );
};


}


#endif //FLATLAND_MOUSE_MOVED_EVENT_H

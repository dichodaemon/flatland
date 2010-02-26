#ifndef FLATLAND_MOUSE_EVENT_H
#define FLATLAND_MOUSE_EVENT_H


#include "Event.h"


namespace Flatland
{

class MouseEvent : public Event
{
public:
  enum Button {
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT
  };
  
  MouseEvent( int x, int y );
  int x() const;
  int y() const;
private:
  int _x;
  int _y;
};


}


#endif //FLATLAND_MOUSE_EVENT_H

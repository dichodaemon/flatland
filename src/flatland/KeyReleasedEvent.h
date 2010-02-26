#ifndef FLATLAND_KEY_RELEASED_EVENT_H
#define FLATLAND_KEY_RELEASED_EVENT_H


#include "KeyboardEvent.h"

namespace Flatland
{

class KeyReleasedEvent : public KeyboardEvent
{
public:
  KeyReleasedEvent( Keys key );
};


}


#endif //FLATLAND_KEY_RELEASED_EVENT_H

#ifndef FLATLAND_KEY_PRESSED_EVENT_H
#define FLATLAND_KEY_PRESSED_EVENT_H


#include "KeyboardEvent.h"

namespace Flatland
{

class KeyPressedEvent : public KeyboardEvent
{
public:
  KeyPressedEvent( Keys key );
};


}


#endif //FLATLAND_KEY_PRESSED_EVENT_H

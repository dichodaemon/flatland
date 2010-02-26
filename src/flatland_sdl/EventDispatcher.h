#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H


#include "SDLObject.h"
#include <flatland/EventDispatcherBase.h>


namespace Flatland
{
  class Bus;
}


class EventDispatcher : public Flatland::EventDispatcherBase
{
public:
  EventDispatcher( Flatland::Bus & bus );
  bool dispatch();
private:
  SDLObject       _sdl;
  Flatland::Bus & _bus;
};


extern "C"
{
  Flatland::EventDispatcherBase * newEventDispatcher( Flatland::Bus & bus );
}


#endif //EVENT_DISPATCHER_H

#ifndef FLATLAND_EVENT_DISPATCHER_H
#define FLATLAND_EVENT_DISPATCHER_H


#include "EventDispatcherBase.h"


namespace Flatland
{


class Bus;


class EventDispatcher : public EventDispatcherBase
{
public:
  EventDispatcher( Bus & bus );
  virtual ~EventDispatcher();
  bool dispatch();
private:
  EventDispatcherBase * _impl;
};


}


#endif //FLATLAND_EVENT_DISPATCHER_H

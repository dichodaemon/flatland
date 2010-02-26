#ifndef FLATLAND_EVENT_DISPATCHER_BASE_H
#define FLATLAND_EVENT_DISPATCHER_BASE_H


namespace Flatland
{


class Bus;


class EventDispatcherBase
{
public:
  typedef EventDispatcherBase * (*Factory)( Bus &);
  virtual ~EventDispatcherBase();
  virtual bool dispatch() = 0;
};


}


#endif //FLATLAND_EVENT_DISPATCHER_BASE_H

#ifndef FLATLAND_EVENT_ADAPTER_H
#define FLATLAND_EVENT_ADAPTER_H


namespace Flatland
{


class Event;


class EventAdapter
{
public:
  virtual ~EventAdapter();
  void callHandler( const Event & event );

private:
  virtual void handle( const Event & event ) = 0;
};


}


#endif //FLATLAND_EVENT_ADAPTER_H

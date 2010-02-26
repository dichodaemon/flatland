#ifndef FLATLAND_TYPED_EVENT_H
#define FLATLAND_TYPED_EVENT_H


#include "Event.h"


namespace Flatland
{


template <class T>
class TypedEvent : public Event
{
public:
  TypedEvent( const T & value );

  T operator()() const;

private:
  T _value;
};

}


#include "TypedEvent.tpp"


#endif //FLATLAND_TYPED_EVENT_H

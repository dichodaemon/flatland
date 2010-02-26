#ifndef FLATLAND_DISCRETE_EVENT_H
#define FLATLAND_DISCRETE_EVENT_H


#include "Event.h"
#include <string>


namespace Flatland
{


class DiscreteEvent : public Event
{
public:
  DiscreteEvent( const std::string & label );
  std::string label() const;

private:
  std::string _label;

};


}

#endif //FLATLAND_DISCRETE_EVENT_H

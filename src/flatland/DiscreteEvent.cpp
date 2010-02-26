#include "DiscreteEvent.h"

using namespace Flatland;
using namespace std;

//------------------------------------------------------------------------------

Flatland::DiscreteEvent::DiscreteEvent( const std::string & label )
  : _label( label )
{
}

//------------------------------------------------------------------------------

std::string
Flatland::DiscreteEvent::label() const
{
   return _label;
}

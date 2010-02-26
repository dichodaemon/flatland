#include "EventAdapter.h"

//------------------------------------------------------------------------------

Flatland::EventAdapter::~EventAdapter()
{
}

//------------------------------------------------------------------------------

void
Flatland::EventAdapter::callHandler( const Event & event )
{
  handle( event );
}

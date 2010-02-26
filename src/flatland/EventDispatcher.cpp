#include "EventDispatcher.h"
#include "ClassLoader.h"

//------------------------------------------------------------------------------

Flatland::EventDispatcher::EventDispatcher( Bus & bus )
  : _impl( ClassLoader<EventDispatcherBase>::loadFactory( "newEventDispatcher" )( bus ) )
{
}

//------------------------------------------------------------------------------

Flatland::EventDispatcher::~EventDispatcher()
{
  delete _impl;
}

//------------------------------------------------------------------------------

bool
Flatland::EventDispatcher::dispatch()
{
  return _impl->dispatch();
}

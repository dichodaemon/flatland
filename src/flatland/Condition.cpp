#include "Condition.h"
#include "Mutex.h"

#ifdef PTHREADS
  #include <flatland_pthreads/ConditionImpl.cpp>
#endif

using namespace Flatland;

//------------------------------------------------------------------------------

Condition::Condition()
  : _impl( new ConditionImpl() )
{
}

//------------------------------------------------------------------------------

Condition::~Condition()
{ 
  delete _impl;
}
  
//------------------------------------------------------------------------------

bool 
Condition::wait( Mutex & mutex, double seconds )
{
  return _impl->wait( *( mutex._mutex ), seconds );
}

//------------------------------------------------------------------------------

void 
Condition::notify()
{
  _impl->notify();
}

//------------------------------------------------------------------------------

void 
Condition::notifyAll()
{
  _impl->notifyAll();
}

#include "Mutex.h"

#ifdef PTHREADS
  #include <flatland_pthreads/MutexImpl.cpp>
#endif

using namespace Flatland;

//------------------------------------------------------------------------------

Mutex::Mutex()
  : _mutex( new MutexImpl() )
{
}

//------------------------------------------------------------------------------

Mutex::~Mutex()
{
  delete _mutex;
}

//------------------------------------------------------------------------------

void 
Mutex::lock()
{
  _mutex->lock();
}

//------------------------------------------------------------------------------

void 
Mutex::unlock()
{
  _mutex->unlock();
}
  

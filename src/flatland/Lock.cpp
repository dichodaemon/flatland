#include "Lock.h"
#include "Mutex.h"

using namespace Flatland;

//------------------------------------------------------------------------------
  
Lock::Lock( Mutex & mutex )
  : _mutex( mutex )
{
  _mutex.lock();
}

//------------------------------------------------------------------------------
  
Lock::~Lock()
{
  _mutex.unlock();
}

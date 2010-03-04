#include "MutexImpl.h"

using namespace Flatland;

//------------------------------------------------------------------------------

MutexImpl::MutexImpl()
{
  pthread_mutexattr_t attributes;
  pthread_mutexattr_init( &attributes );
  pthread_mutexattr_settype( &attributes, PTHREAD_MUTEX_RECURSIVE );
  pthread_mutex_init( &_mutex, &attributes );
}

//------------------------------------------------------------------------------

MutexImpl::~MutexImpl()
{
  pthread_mutex_destroy( &_mutex );
}

//------------------------------------------------------------------------------

void
MutexImpl::lock()
{
  pthread_mutex_lock( &_mutex );
}

//------------------------------------------------------------------------------

void
MutexImpl::unlock()
{
  pthread_mutex_unlock( &_mutex );
}

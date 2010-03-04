#include "ThreadImpl.h"
#include <cmath>

using namespace Flatland;

//------------------------------------------------------------------------------

ThreadImpl::ThreadImpl( bool detached ) 
  : _detached( detached )
{ 
}

//------------------------------------------------------------------------------

ThreadImpl::~ThreadImpl() { 
}

//------------------------------------------------------------------------------

void 
ThreadImpl::start( 
  FunctionPointer  function = 0, 
  void *           arguments = 0 ) 
{
  if ( function == 0 ) {
    function  = ThreadImpl::startThread;
    arguments = this;
  }
  pthread_attr_t attributes;
  pthread_attr_init( &attributes );
  pthread_attr_setscope( &attributes, PTHREAD_SCOPE_SYSTEM );
  
  if ( _detached ) {
    pthread_attr_setdetachstate( &attributes, PTHREAD_CREATE_DETACHED ); 
  }
  
  pthread_create( &_thread, &attributes, function, arguments );
  pthread_attr_destroy( &attributes );
}

//------------------------------------------------------------------------------

void * 
ThreadImpl::join() 
{
  pthread_join( _thread, NULL );
  return _result;
}

//------------------------------------------------------------------------------

void 
ThreadImpl::sleep( double seconds ) 
{
  timespec nominal;
  timespec remaining;
  nominal.tv_sec  = floor( seconds );
  nominal.tv_nsec = ( seconds - nominal.tv_sec ) * 1E9;
  nanosleep( &nominal, &remaining );
}

//------------------------------------------------------------------------------

void 
ThreadImpl::yield() 
{
  sched_yield();
}

//------------------------------------------------------------------------------

void *
ThreadImpl::run() 
{
  return NULL;
}

//------------------------------------------------------------------------------

void * 
ThreadImpl::startThread( void * self ) 
{
  ThreadImpl* thread = static_cast<ThreadImpl*>( self );
  thread->_result = thread->run();
  return thread->_result;
}


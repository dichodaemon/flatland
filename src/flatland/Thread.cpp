#include "Thread.h"

#ifdef PTHREADS
  #include <flatland_pthreads/ThreadImpl.cpp>
#endif

using namespace Flatland;

//------------------------------------------------------------------------------

Thread::Thread( bool detached )
  : _thread( new ThreadImpl( detached ) )
{
}

//------------------------------------------------------------------------------
  
Thread::~Thread()
{
  delete _thread;
}
  
//------------------------------------------------------------------------------

void 
Thread::start( FunctionPointer function, void * arguments )
{
  if ( function == 0 ) {
    function  = Thread::startThread;
    arguments = this;
  }
  _thread->start( function, arguments );
}

//------------------------------------------------------------------------------
  
void * 
Thread::join()
{
  return _thread->join();
}

//------------------------------------------------------------------------------
  
void 
Thread::sleep( double seconds )
{
  ThreadImpl::sleep( seconds );
}

//------------------------------------------------------------------------------
  
void 
Thread::yield()
{
  ThreadImpl::yield();
}

//------------------------------------------------------------------------------
  
void *
Thread::run()
{
  return NULL;
}

//------------------------------------------------------------------------------

void * Thread::startThread( void * self ) 
{
  Thread * thread = reinterpret_cast<Thread*>( self );
  thread->_result = thread->run();
  return thread->_result;
}

#ifndef FLATLAND_THREAD_IMPL_H
#define FLATLAND_THREAD_IMPL_H


#include <pthread.h>


namespace Flatland {


class ThreadImpl
{
public:
  typedef void * (* FunctionPointer)( void * );

  ThreadImpl( bool detached = false );
  virtual ~ThreadImpl();
  void start( FunctionPointer function, void * arguments );
  void * join();
  static void sleep( double seconds );
  static void yield();

private:
  ThreadImpl( const ThreadImpl & );
  void operator=( const ThreadImpl & );
  virtual void * run();

  static void * startThread( void * self );

  pthread_t      _thread;
  bool           _detached;
  void *         _result;
};


}


#endif //FLATLAND_THREAD_IMPL_H

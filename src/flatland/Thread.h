#ifndef FLATLAND_THREAD_H
#define FLATLAND_THREAD_H


namespace Flatland {


class ThreadImpl;


class Thread
{
public:
  typedef void * (* FunctionPointer)( void * );

  Thread( bool detached = false );
  virtual ~Thread();
  virtual void start( FunctionPointer function = 0, void * arguments = 0 );
  void * join();
  static void sleep( double seconds );
  static void yield();

protected:
  static void * startThread( void * self );

private:
  Thread( const Thread & );
  void operator=( const Thread & );
  virtual void * run();


  ThreadImpl * _thread;
  void *       _result;
};


}


#endif //FLATLAND_THREAD_H

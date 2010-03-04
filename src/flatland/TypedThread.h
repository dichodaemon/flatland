#ifndef FLATLAND_TYPED_THREAD_H
#define FLATLAND_TYPED_THREAD_H


#include "Thread.h"


namespace Flatland
{


template <typename T>
class TypedThread : public Thread
{
public:
  TypedThread( T & functor );
  T & functor();
  
private:
  virtual void * run();
  
  T & _functor;
};

template <typename T>
TypedThread<T> * typedThread( T & functor );

#include "TypedThread.tpp"

}


#endif //FLATLAND_TYPED_THREAD_H


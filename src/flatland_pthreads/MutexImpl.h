#ifndef FLATLAND_MUTEX_IMPL_H
#define FLATLAND_MUTEX_IMPL_H


#include <pthread.h>


namespace Flatland {


class MutexImpl
{
public:
  MutexImpl();
  ~MutexImpl();
  
  void lock();
  void unlock();
  
  friend class ConditionImpl;
private:
  MutexImpl( const MutexImpl & );
  void operator=( const MutexImpl & );
  
  pthread_mutex_t _mutex;
};


}


#endif //FLATLAND_MUTEX_IMPL_H

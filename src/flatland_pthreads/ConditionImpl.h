#ifndef FLATLAND_CONDITION_IMPL_H
#define FLATLAND_CONDITION_IMPL_H


#include<pthread.h>


namespace Flatland {


class MutexImpl;

class ConditionImpl
{
public:
  ConditionImpl();
  virtual ~ConditionImpl();
  
  bool wait( MutexImpl & mutex, double seconds );
  void notify();
  void notifyAll();
  
private:
  ConditionImpl( const ConditionImpl & );
  void operator=( const ConditionImpl & );
  
  pthread_cond_t _condition;
  
};


}


#endif //FLATLAND_CONDITION_IMPL_H

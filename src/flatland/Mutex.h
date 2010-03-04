#ifndef FLATLAND_MUTEX_H
#define FLATLAND_MUTEX_H


namespace Flatland 
{


class MutexImpl;


class Mutex
{
public:
  Mutex();
  ~Mutex();

  void lock();
  void unlock();

  friend class Condition;

private:
  Mutex( const Mutex & );
  void operator=( const Mutex & );


  MutexImpl * _mutex;
};


}


#endif //FLATLAND_MUTEX_H

#ifndef FLATLAND_LOCK_H
#define FLATLAND_LOCK_H


namespace Flatland 
{


class Mutex;


class Lock
{
public:
  Lock( Mutex & mutex );
  ~Lock();

private:
  Lock( const Lock & );
  void operator=( const Lock & );
  
  Mutex & _mutex;
};


}


#endif //FLATLAND_LOCK_H

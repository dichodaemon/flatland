#ifndef FLATLAND_CONDITION_H
#define FLATLAND_CONDITION_H


namespace Flatland 
{

class ConditionImpl;
class Mutex;


class Condition
{
public:
  Condition();
  virtual ~Condition();

  bool wait( Mutex & mutex, double seconds );
  void notify();
  void notifyAll();

private:
  Condition( const Condition & );
  void operator=( const Condition & );

  ConditionImpl * _impl;

};


}


#endif // FLATLAND_CONDITION_H

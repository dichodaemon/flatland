#ifndef FLATLAND_MEMBER_FUNCTION_ADAPTER_H
#define FLATLAND_MEMBER_FUNCTION_ADAPTER_H


#include "EventAdapter.h"


namespace Flatland
{


template < class T, class EVENT >
class MemberFunctionAdapter : public EventAdapter
{
public:
  typedef void (T::*MemberFunction)(EVENT&);

  MemberFunctionAdapter( T & instance, MemberFunction handler );

  void handle( const Event & event );

private:
  T &            _object;
  MemberFunction _handler;

};


}


#include "MemberFunctionAdapter.tpp"

#endif //FLATLAND_MEMBER_FUNCTION_ADAPTER_H

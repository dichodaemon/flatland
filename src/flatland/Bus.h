#ifndef FLATLAND_BUS_H
#define FLATLAND_BUS_H


#include "MemberFunctionAdapter.h"
#include "TypeInfo.h"
#include <map>
#include <deque>
#include <string>


namespace Flatland
{


class Event;


class Bus
{
public:
  virtual ~Bus();
  
  template < class EVENT >
  void send( const EVENT & event );

  template < class T, class EVENT >
  void subscribe( T & object, void ( T::*handler )( EVENT& ) );

  template < class EVENT >
  void send( const std::string & name, const EVENT & event );

  template < class T, class EVENT >
  void subscribe(
    const std::string & name,
    T & object,
    void ( T::*handler )( EVENT& )
  );
private:
  typedef std::deque< EventAdapter * >           HandlerList;
  typedef std::map< TypeInfo, HandlerList >      HandlerMap;
  typedef std::map< std::string, HandlerList >   NamedHandlerList;
  typedef std::map< TypeInfo, NamedHandlerList > NamedHandlerMap;

  HandlerMap      _handlers;
	NamedHandlerMap _namedHandlers;
};


}


#include "Bus.tpp"


#endif //FLATLAND_BUS_H
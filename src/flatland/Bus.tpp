
//------------------------------------------------------------------------------

template < class T, class EVENT >
void
Flatland::Bus::subscribe( T & object, void ( T::*handler )( EVENT& ) )
{
  HandlerList & list = _handlers[TypeInfo( typeid( EVENT ) )];
  list.push_back( new MemberFunctionAdapter< T, EVENT >( object, handler ) );
}

//------------------------------------------------------------------------------

template< class EVENT >
void
Flatland::Bus::send( const EVENT & event )
{
  TypeInfo typeInfo = TypeInfo( typeid( EVENT ) );
  if ( _handlers.find( typeInfo ) != _handlers.end() ) {
    HandlerList & list = _handlers[typeInfo];
    HandlerList::iterator i;
    HandlerList::iterator end = list.end();
    for ( i = list.begin(); i != end; ++i ) {
      (*i)->callHandler( event );
    }
  }
}

//------------------------------------------------------------------------------

template < class T, class EVENT >
void
Flatland::Bus::subscribe(
  const std::string & name,
  T & object,
  void ( T::*handler )( EVENT& )
)
{
  NamedHandlerList & namedList = _namedHandlers[TypeInfo( typeid( EVENT ) )];
  HandlerList & list = namedList[name];
  list.push_back( new MemberFunctionAdapter< T, EVENT >( object, handler ) );
}

//------------------------------------------------------------------------------

template< class EVENT >
void
Flatland::Bus::send( const std::string & name, const EVENT & event )
{
  TypeInfo typeInfo = TypeInfo( typeid( EVENT ) );
  if ( _namedHandlers.find( typeInfo ) != _namedHandlers.end() )
  {
    NamedHandlerList & namedList = _namedHandlers[TypeInfo( typeid( EVENT ) )];
    if ( namedList.find( name ) != namedList.end() )
    {
      HandlerList & list = namedList[name];
      HandlerList::iterator i;
      HandlerList::iterator end = list.end();
      for ( i = list.begin(); i != end; ++i )
      {
        (*i)->callHandler( event );
      }
    }
  }
}

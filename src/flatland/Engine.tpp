
//------------------------------------------------------------------------------

template < class T, class EVENT >
void
Flatland::Engine::subscribe( T & object, void ( T::*handler )( EVENT& ) )
{
  _bus.subscribe( object, handler );
}

//------------------------------------------------------------------------------

template < class EVENT >
void
Flatland::Engine::send( const EVENT & event )
{
  _bus.send( event );
}

//------------------------------------------------------------------------------

template < class EVENT >
void
Flatland::Engine::send( const std::string & name, const EVENT & event )
{
  _bus.send( name, event );
}

//------------------------------------------------------------------------------

template < class T, class EVENT >
void
Flatland::Engine::subscribe(
  const std::string & name,
  T & object,
  void ( T::*handler )( EVENT& )
)
{
  _bus.subscribe( name, object, handler );
}

//------------------------------------------------------------------------------

template < class T >
void
Flatland::Engine::addPainter(
  T & instance,
  void (T::*method)( GraphicsContext & ),
  double depth
)
{
  _paintQueue.addPainter( instance, method, depth );
}

//------------------------------------------------------------------------------

template < class T >
void
Flatland::Engine::removePainter(
  T & instance, void (T::*method)( GraphicsContext & )
)
{
  _paintQueue.removePainter( instance, method );
}


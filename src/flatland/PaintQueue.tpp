#include <cstdio>
//------------------------------------------------------------------------------

template < class T >
void
Flatland::PaintQueue::addPainter(
  T & instance,
  void (T::*method)( GraphicsContext & ),
  double depth
)
{
  PainterAdapter< T > * p = new PainterAdapter< T >( instance, method );
  addPainter( *p, depth );
  _adapters.insert( p );
  _adapterIndex[(void *) &instance].insert( p );
}

//------------------------------------------------------------------------------

template < class T >
void
Flatland::PaintQueue::removePainter(
  T & instance,
  void (T::*method)( GraphicsContext & )
)
{
  Painters & painters = _adapterIndex[(void *) &instance];
  Painters::iterator i;
  Painters::iterator iend = painters.end();
  for ( i = painters.begin(); i != iend; ++i )
  {
    PainterAdapter<T> * adapter = dynamic_cast< PainterAdapter<T> * >( *i );
    if ( adapter->_handler == method )
    {
      _adapterIndex.erase( &instance );
      _adapters.erase( adapter );
      removePainter( *adapter );
      delete adapter;
      break;
    }
  }
}


//------------------------------------------------------------------------------

template < class T >
Flatland::PainterAdapter< T >::PainterAdapter(
  T & object,
  MemberFunction handler
) : _object( object ),
    _handler( handler )
{}

//------------------------------------------------------------------------------

template < class T >
void
Flatland::PainterAdapter< T >::paint( GraphicsContext & graphics )
{
  ( _object.*_handler )( graphics );
}

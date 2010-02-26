
//------------------------------------------------------------------------------

template < class T, class EVENT >
Flatland::MemberFunctionAdapter< T, EVENT >::MemberFunctionAdapter(
  T & object,
  MemberFunction handler
) : _object( object ),
    _handler( handler )
{}

//------------------------------------------------------------------------------

template < class T, class EVENT >
void
Flatland::MemberFunctionAdapter< T, EVENT >::handle( const Event & event )
{
  ( _object.*_handler )( *static_cast<EVENT*>( &event ) );
}

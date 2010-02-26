//------------------------------------------------------------------------------

template< class T>
Flatland::TypedEvent<T>::TypedEvent( const T & value )
  : _value( value )
{
}

//------------------------------------------------------------------------------

template< class T>
inline
T
Flatland::TypedEvent<T>::operator()() const
{
  return _value;
}


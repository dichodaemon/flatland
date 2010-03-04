//------------------------------------------------------------------------------

template <typename T>
TypedThread<T>::TypedThread( T & functor )
  : _functor( functor )
{
}

//------------------------------------------------------------------------------

template <typename T>
void * 
TypedThread<T>::run()
{
  return reinterpret_cast<void *>( _functor() );
}

//------------------------------------------------------------------------------

template <typename T>
T & 
TypedThread<T>::functor()
{
  return _functor;
}

//------------------------------------------------------------------------------

template <typename T>
TypedThread<T> * typedThread( T & functor )
{
  return new TypedThread<T>( functor );
}


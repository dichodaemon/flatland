
//------------------------------------------------------------------------------

template <typename T, class RELEASER>
Queue<T, RELEASER>::Queue( size_t capacity, QueuePolicy policy )
  : _capacity( capacity ),
    _policy( policy )
{
}

//------------------------------------------------------------------------------
  
template <typename T, class RELEASER>
void 
Queue<T, RELEASER>::push( const T & value, double timeout ) throw ( TimeoutException)
{
  _mutex.lock();
  if ( _capacity > 0 && _queue.size() == _capacity ) {
    if ( _policy == WAIT_WHEN_FULL ) {
      while ( _queue.size() == _capacity ) {
        if ( ! _notFull.wait( _mutex, timeout ) ) {
          throw TimeoutException( "Timeout in queue" );
        }
      }
    } else if ( _policy == DISCARD_OLDEST ) {
      RELEASER::release( _queue.front() ); 
      _queue.pop();
      _queue.push( value );
      _mutex.unlock();
      return;
    } else {
      _mutex.unlock();
      return;
    }
  }
  _queue.push( value );
  _mutex.unlock();
  _notEmpty.notify();
}

//------------------------------------------------------------------------------
  
template <typename T, class RELEASER>
T &
Queue<T, RELEASER>::next( double timeout ) throw ( TimeoutException )
{
  Lock lock( _mutex );
  while ( _queue.empty() ) {
    if ( ! _notEmpty.wait( _mutex, timeout ) ) {
      throw TimeoutException( "Timeout in queue" );
    }
  }
  return _queue.front();
}

//------------------------------------------------------------------------------
  
template <typename T, class RELEASER>
void
Queue<T, RELEASER>::pop( double timeout ) throw ( TimeoutException )
{
  Lock lock( _mutex );
  while ( _queue.empty() ) {
    if ( ! _notEmpty.wait( _mutex, timeout ) ) {
      throw TimeoutException( "Timeout in queue" );
    }
  }
  _queue.pop();
  _notFull.notify();
}

//------------------------------------------------------------------------------
  
template <typename T, class RELEASER>
T
Queue<T, RELEASER>::popNext( double timeout ) throw ( TimeoutException )
{
  Lock lock( _mutex );
  while ( _queue.empty() ) {
    if ( ! _notEmpty.wait( _mutex, timeout ) ) {
      throw TimeoutException( "Timeout in queue" );
    }
  }
  T result = _queue.front();
  _queue.pop();
  _notFull.notify();
  return result;
}

//------------------------------------------------------------------------------
  
template <typename T, class RELEASER>
bool
Queue<T, RELEASER>::empty()
{
  Lock lock( _mutex );
  return _queue.empty();
}


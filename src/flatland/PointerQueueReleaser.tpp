//------------------------------------------------------------------------------

template <typename T>
void 
PointerQueueReleaser<T>::release( T value )
{
  delete value;
}

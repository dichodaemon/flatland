//------------------------------------------------------------------------------

template < class T >
std::string Flatland::ClassLoader< T >::_searchPath;

template < class T >
std::string Flatland::ClassLoader< T >::_libraryName;

//------------------------------------------------------------------------------

template < class T >
void
Flatland::ClassLoader< T >::searchPath( const std::string & value )
{
  _searchPath = value;
}

//------------------------------------------------------------------------------

template < class T >
void
Flatland::ClassLoader< T >::libraryName( const std::string & value )
{
  _libraryName = value;
}

//------------------------------------------------------------------------------

template < class T >
typename Flatland::ClassLoader< T >::Factory
Flatland::ClassLoader< T >::loadFactory( const std::string & factoryName )
{
  return loadFactory< typename T::Factory >( factoryName );
}

//------------------------------------------------------------------------------

template < class T >
template < class FACTORY >
FACTORY
Flatland::ClassLoader< T >::loadFactory( const std::string & factoryName )
{
  size_t flags = RTLD_NOW | RTLD_GLOBAL;
  void * handle = dlopen( findFile( "lib" + _libraryName + ".so", _searchPath ).c_str(), flags );
  if( handle == 0 ) {
    Logger::error( std::string( "Error: %s\n" ) + dlerror(), "ClassLoader" );
    handle = dlopen( findFile( _libraryName + ".so", _searchPath ).c_str(), flags );
    if ( handle == 0 ) {
      throw ClassLoadingError( "Unable to open class lib: " + _libraryName + " (" + factoryName + ")\nError:" + dlerror() );
    }
  }

  FACTORY factory = reinterpret_cast< FACTORY >( dlsym( handle, factoryName.c_str() ) );

  if( factory == 0 ) {
    dlclose( handle );
    throw ClassLoadingError( "Factory function '" + factoryName + "' not found for: " + _libraryName );
  }
  return factory;
}


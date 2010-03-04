#ifndef FLATLAND_CLASS_LOADER_H
#define FLATLAND_CLASS_LOADER_H


#include "Exceptions.h"
#include "FileUtils.h"
#include "Logger.h"
#include "Platform.h"
#include <string>
#include <dlfcn.h>

#ifdef PLUGIN_LIBRARIES
  #define FACTORY( CLASSNAME, FACTORYNAME ) \
  ClassLoader<CLASSNAME>::loadFactory( #FACTORYNAME )
#else
  #define FACTORY( CLASSNAME, FACTORYNAME ) \
  FACTORYNAME
#endif


namespace Flatland
{


template< class T >
class ClassLoader
{
public:
  typedef typename T::Factory Factory;
  static void searchPath( const std::string & value );
  static void libraryName( const std::string & value );

  static Factory loadFactory( const std::string & factoryName );
  
  template < class FACTORY >
  static FACTORY loadFactory( const std::string & factoryName );


private:
  static std::string _searchPath;
  static std::string _libraryName;
};


}


#include "ClassLoader.tpp"


#endif //FLATLAND_CLASS_LOADER_H

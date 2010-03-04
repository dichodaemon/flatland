#include "Configuration.h"
extern "C" {
  #include <iniparser/iniparser.h>
}
#include <cfloat>

using namespace std;

//------------------------------------------------------------------------------

namespace Flatland {
  struct Configuration::ConfigurationImpl
  {
    dictionary * d;
  };
}

//------------------------------------------------------------------------------

string makeKey( const std::string & section, const std::string & key )
{
  string result( section + ":" + key );
  transform( result.begin(), result.end(), result.begin(), (int(*)(int)) tolower );
  return result;
}

//------------------------------------------------------------------------------

Flatland::Configuration::Configuration( const std::string & filename )
  : _data( new ConfigurationImpl() )
{
  _data->d = iniparser_load( filename.c_str() );
}

//------------------------------------------------------------------------------

Flatland::Configuration::~Configuration()
{
  iniparser_freedict( _data->d );
  delete _data;
}

//------------------------------------------------------------------------------

int
Flatland::Configuration::getInt(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  int result   = iniparser_getint(
    _data->d,
    makeKey( section, key ).c_str(),
    INT_MAX
  );
  if ( result == INT_MAX ) {
    throw WrongKeyException(
      "No value for section:" + section + ", key: " + key
    );
  }
  return result;
}

//------------------------------------------------------------------------------

double
Flatland::Configuration::getDouble(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  double result = iniparser_getdouble(
    _data->d,
    makeKey( section, key ).c_str(),
    DBL_MAX
  );
  if ( result == DBL_MAX ) {
    throw WrongKeyException(
      "No value for section:" + section + ", key: " + key
    );
  }
  return result;
}

//------------------------------------------------------------------------------

std::string
Flatland::Configuration::getString(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  const char * value = "";
  std::string result( iniparser_getstring(
    _data->d,
    makeKey( section, key ).c_str(),
    const_cast<char *>( value ) )
  );
  if ( result == "" ) {
    throw WrongKeyException(
      "No value for section:" + section + ", key: " + key
    );
  }
  return result;
}

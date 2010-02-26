#include "ConfigurationImpl.h"
#include <algorithm>
#include <string>
#include <cfloat>
#include <climits>

using namespace std;

//------------------------------------------------------------------------------

string makeKey( const std::string & section, const std::string & key )
{
  string result( section + ":" + key );
  transform( result.begin(), result.end(), result.begin(), (int(*)(int)) tolower );
  return result;
}

//------------------------------------------------------------------------------

Flatland::ConfigurationImpl::ConfigurationImpl( const std::string & filename )
{
  _dictionary = iniparser_load( filename.c_str() );
}

//------------------------------------------------------------------------------

Flatland::ConfigurationImpl::~ConfigurationImpl()
{
  iniparser_freedict( _dictionary );
}

//------------------------------------------------------------------------------

int
Flatland::ConfigurationImpl::getInt(
  const std::string & section,
  const std::string & key
)
throw ( WrongKeyException )
{
  int result   = iniparser_getint(
    _dictionary,
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
Flatland::ConfigurationImpl::getDouble(
  const std::string & section,
  const std::string & key
)
throw ( WrongKeyException )
{
  double result = iniparser_getdouble(
    _dictionary,
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
Flatland::ConfigurationImpl::getString(
  const std::string & section,
  const std::string & key
)
throw ( WrongKeyException )
{
  const char * value = "";
  std::string result( iniparser_getstring(
    _dictionary,
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

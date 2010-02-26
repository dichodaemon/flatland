#include "Configuration.h"
#include <_flatland/ConfigurationImpl.h>

//------------------------------------------------------------------------------

Flatland::Configuration::Configuration( const std::string & filename )
{
  _impl = new ConfigurationImpl( filename );
}

//------------------------------------------------------------------------------

Flatland::Configuration::~Configuration()
{
  delete _impl;
}

//------------------------------------------------------------------------------

int
Flatland::Configuration::getInt(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  return _impl->getInt( section, key );
}

//------------------------------------------------------------------------------

double
Flatland::Configuration::getDouble(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  return _impl->getDouble( section, key );
}

//------------------------------------------------------------------------------

std::string
Flatland::Configuration::getString(
  const std::string & section,
  const std::string & key
) const
throw ( WrongKeyException )
{
  return _impl->getString( section, key );
}

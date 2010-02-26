#ifndef FLATLAND_CONFIGURATION_IMPL_H
#define FLATLAND_CONFIGURATION_IMPL_H


#include <flatland/Exceptions.h>
extern "C" {
  #include <iniparser/iniparser.h>
}


namespace Flatland
{


class ConfigurationImpl
{
public:
  ConfigurationImpl( const std::string & filename );

  ~ConfigurationImpl();

  int getInt( const std::string & section, const std::string & key )
  throw ( WrongKeyException );

  double getDouble( const std::string & section, const std::string & key )
  throw ( WrongKeyException );

  std::string getString( const std::string & section, const std::string & key )
  throw ( WrongKeyException );

private:
  dictionary * _dictionary;
  
};


}


#endif //FLATLAND_CONFIGURATION_IMPL_H

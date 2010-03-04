#ifndef FLATLAND_CONFIGURATION_H
#define FLATLAND_CONFIGURATION_H


#include "Exceptions.h"
#include <string>


namespace Flatland
{


class Configuration
{
public:
  /**
   * Initializes a new configuration object from a file.
   *
   * @param filename Configuration file name.
   */
  Configuration( const std::string & filename );

  ~Configuration();

  /**
   * Returns the value as an integer.
   *
   * @param section Section name.
   * @param section Key name.
   * @return integer value.
   */
  int getInt( const std::string & section, const std::string & key ) const
  throw ( WrongKeyException );
  
  /**
   * Returns the value as a double.
   *
   * @param section Section name.
   * @param section Key name.
   * @return double value.
   */
  double getDouble( const std::string & section, const std::string & key ) const
  throw ( WrongKeyException );

  /**
   * Returns the value as a string.
   *
   * @param section Section name.
   * @param section Key name.
   * @return string value.
   */
  std::string getString( const std::string & section, const std::string & key ) const
  throw ( WrongKeyException );

private:
  struct ConfigurationImpl;
  ConfigurationImpl * _data;
};


}


#endif //FLATLAND_CONFIGURATION_H

#ifndef FLATLAND_LOGGER_H
#define FLATLAND_LOGGER_H


#include <ostream>
#include <map>


namespace Flatland
{


class Logger
{
public:
  enum Level {
    NONE    = 0,
    ERROR   = 1,
    WARNING = 2,
    INFO    = 3,
    DEBUG   = 4,
    SPAM    = 5
  };

  static void setLevel( Level level, const std::string & group = "default" );
  static void setErrorOutput( std::ostream & stream );
  static void setWarningOutput( std::ostream & stream );
  static void setInfoOutput( std::ostream & stream );
  static void setDebugOutput( std::ostream & stream );
  static void setSpamOutput( std::ostream & stream );

  static void error(
    const std::string & message,
    const std::string & group = "default" );
  static void warning(
    const std::string & message,
    const std::string & group = "default" );
  static void info(
    const std::string & message,
    const std::string & group = "default" );
  static void debug(
    const std::string & message,
    const std::string & group = "default" );
  static void spam(
    const std::string & message,
    const std::string & group = "default" );

private:
  typedef std::map<std::string, Level> LevelMap;

  static void printMessage(
    Level level,
    const std::string & levelName,
    std::ostream & stream,
    const std::string & message,
    const std::string & group );

  static LevelMap       _levels;
  static std::ostream * _errorStream;
  static std::ostream * _warningStream;
  static std::ostream * _infoStream;
  static std::ostream * _debugStream;
  static std::ostream * _spamStream;
};


}


#endif //FLATLAND_LOGGER_H

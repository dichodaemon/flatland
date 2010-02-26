#include "Logger.h"
#include <ostream>
#include <iostream>

using namespace Flatland;
using namespace std;

//------------------------------------------------------------------------------

Logger::LevelMap Logger::_levels;
ostream * Logger::_errorStream   = &cerr; 
ostream * Logger::_warningStream = &cerr; 
ostream * Logger::_infoStream    = &cout; 
ostream * Logger::_debugStream   = &cout; 
ostream * Logger::_spamStream    = &cout; 

//------------------------------------------------------------------------------

void 
Logger::setLevel( Level level, const string & group )
{
  _levels[group] = level;
}

//------------------------------------------------------------------------------

void 
Logger::setErrorOutput( ostream & stream )
{
  _errorStream = &stream;
}

//------------------------------------------------------------------------------

void 
Logger::setWarningOutput( ostream & stream )
{
  _warningStream = &stream;
}

//------------------------------------------------------------------------------

void 
Logger::setInfoOutput( ostream & stream )
{
  _infoStream = &stream;
}

//------------------------------------------------------------------------------

void 
Logger::setDebugOutput( ostream & stream )
{
  _debugStream = &stream;
}

//------------------------------------------------------------------------------

void 
Logger::setSpamOutput( ostream & stream )
{
  _spamStream = &stream;
}

//------------------------------------------------------------------------------

void 
Logger::error( const std::string & message, const string & group )
{
  printMessage( ERROR, "ERROR", *_errorStream, message, group );
}

//------------------------------------------------------------------------------

void 
Logger::warning( const std::string & message, const string & group )
{
  printMessage( WARNING, "WARNING", *_warningStream, message, group );
}

//------------------------------------------------------------------------------

void 
Logger::info( const std::string & message, const string & group )
{
  printMessage( INFO, "INFO", *_infoStream, message, group );
}

//------------------------------------------------------------------------------

void 
Logger::debug( const std::string & message, const string & group )
{
  printMessage( DEBUG, "DEBUG", *_debugStream, message, group );
}

//------------------------------------------------------------------------------

void 
Logger::spam( const std::string & message, const string & group )
{
  printMessage( SPAM, "SPAM", *_spamStream, message, group );
}

//------------------------------------------------------------------------------

void
Logger::printMessage( 
  Level level, 
  const string & levelName,
  ostream & levelStream,
  const string & message,
  const string & group )
{
  Level groupLevel      = INFO;
  LevelMap::iterator it = _levels.find( group );
  if ( it != _levels.end() ) {
    groupLevel = it->second;
  } else {
    _levels[group] = groupLevel;
  }
  if ( groupLevel >= level ) {
    levelStream << levelName << " (" << group << "): " << message << endl;
    levelStream.flush();
  }
}

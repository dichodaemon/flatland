#include "SoundManager.h"
#include <flatland/FileUtils.h>
#include <flatland/SoundBuffer.h>

using namespace Flatland;

//------------------------------------------------------------------------------

std::string            SoundManager::_path;
SoundManager::Buffers  SoundManager::_buffers;

//------------------------------------------------------------------------------

SoundBuffer & 
SoundManager::loadSound( const std::string & filename )
{

}

//------------------------------------------------------------------------------

void 
SoundManager::setBaseDirectory( const std::string & path )
{
  _path = path;
}

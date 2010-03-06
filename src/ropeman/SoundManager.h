#ifndef FLATLAND_SOUND_MANAGER_H
#define FLATLAND_SOUND_MANAGER_H


// #include <auto_ptr>
#include <map>
#include <string>


namespace Flatland
{


class SoundBuffer; 

 
class SoundManager
{
public:
  static SoundBuffer & loadSound( const std::string & filename );
  static void setBaseDirectory( const std::string & path );
private:
  typedef std::map< std::string, const std::auto_ptr< SoundBuffer > > Buffers;
  static std::string _path;
  static Buffers     _buffers;
}; 

}


#endif //FLATLAND_SOUND_MANAGER_H

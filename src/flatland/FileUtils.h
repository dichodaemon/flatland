#ifndef FLATLAND_FILEUTILS_H
#define FLATLAND_FILEUTILS_H


#include <string>


namespace Flatland
{

std::string fileContents( const std::string & path );

bool fileExists( const std::string & fullPath );

const std::string findFile( 
  const std::string & fileName,
  const std::string & searchPath );


}


#endif //FLATLAND_FILEUTILS_H

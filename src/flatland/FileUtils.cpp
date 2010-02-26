#include "FileUtils.h"
#include <sys/stat.h>
#include <fstream>
#include <sstream>

using namespace Flatland;
using namespace std;


//------------------------------------------------------------------------------

string 
Flatland::fileContents( const string & path )
{
  string contents;
  string s;
  ifstream in( path.c_str() );
  while ( getline( in, s ) ) { 
    contents += s + "\n";
  }
  return contents;
}

//------------------------------------------------------------------------------

bool 
Flatland::fileExists( const std::string & fullPath )
{
  struct stat fileInfo;
  return stat( fullPath.c_str(), &fileInfo ) == 0;
}

//------------------------------------------------------------------------------

const string 
Flatland::findFile( const string & fileName, const string & searchPath )
{
  if( searchPath.empty() && fileExists( fileName ) ) {
    return fileName;
  }
      
  string delimiters = ":";
  string::size_type p1 = searchPath.find_first_not_of( delimiters, 0 );
  string::size_type p2 = 0;
  p2 = searchPath.find_first_of( delimiters, p2 );
  
  while ( p1 != string::npos || p2 != string::npos ) {
    string currentPath = searchPath.substr( p1, p2 - p1 );
    p1 = searchPath.find_first_not_of( delimiters, p2 );
    p2 = searchPath.find_first_of( delimiters, p1 );
    
    if ( ! currentPath.empty() ) {
      if ( currentPath[currentPath.size() - 1] != '/' ) {
        currentPath += "/";
      }
      string fullPath = currentPath + fileName;
      if ( fileExists( fullPath ) ) {
        return fullPath;
      }
    }
  }
  
  return fileName;
}

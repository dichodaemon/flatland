#ifndef FLATLAND_EXCEPTIONS_H
#define FLATLAND_EXCEPTIONS_H


#include <stdexcept>

namespace Flatland
{

class WrongKeyException : public std::invalid_argument
{
public:
  WrongKeyException( const std::string & message );
};

class FileLoadError : public std::runtime_error
{
public:
  FileLoadError( const std::string & message );
};

}


#endif //FLATLAND_EXCEPTIONS_H

#include "Exceptions.h"

//------------------------------------------------------------------------------

Flatland::WrongKeyException::WrongKeyException( const std::string & message )
  : invalid_argument( message )
{
}

//------------------------------------------------------------------------------

Flatland::ClassLoadingError::ClassLoadingError( const std::string & message )
  : runtime_error( message )
{
}

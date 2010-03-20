#include "Exceptions.h"

//------------------------------------------------------------------------------

Flatland::WrongKeyException::WrongKeyException( const std::string & message )
  : invalid_argument( message )
{
}

//------------------------------------------------------------------------------

Flatland::FileLoadError::FileLoadError( const std::string & message )
  : runtime_error( message )
{
}

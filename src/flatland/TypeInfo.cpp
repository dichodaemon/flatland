#include "TypeInfo.h"

using namespace std;

//------------------------------------------------------------------------------

Flatland::TypeInfo::TypeInfo( const type_info & info)
  : _typeInfo( info )
{
}

//------------------------------------------------------------------------------

bool
Flatland::TypeInfo::operator<( const TypeInfo& rhs ) const
{
  return _typeInfo.before( rhs._typeInfo ) != 0;
}

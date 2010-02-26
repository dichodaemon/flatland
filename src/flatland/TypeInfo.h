#ifndef FLATLAND_TYPEINFO_H
#define FLATLAND_TYPEINFO_H


#include <typeinfo>


namespace Flatland
{


class TypeInfo
{
public:
  explicit TypeInfo( const std::type_info & info );

  bool operator<( const TypeInfo& rhs ) const;

private:
  const std::type_info & _typeInfo;
};


}


#endif //FLATLAND_TYPEINFO_H

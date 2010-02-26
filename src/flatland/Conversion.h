#ifndef FLATLAND_CONVERSION_H
#define FLATLAND_CONVERSION_H


#include <sstream>
#include <iomanip>

namespace Flatland {


template <typename T>
std::string toString( const T & value );

template <typename T>
T fromString( const std::string & input );


#include "Conversion.tpp"

}


#endif //FLATLAND_CONVERSION_H

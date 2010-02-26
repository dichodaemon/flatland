//------------------------------------------------------------------------------

template <typename T>
std::string 
toString( const T & value )
{
  std::stringstream stream;
  stream << std::setprecision( 10 );
  stream << value;
  return stream.str();
}

//------------------------------------------------------------------------------

template <typename T>
T 
fromString( const std::string & input )
{
  T result;
  std::stringstream stream( input );
  stream >> result;
  return result;
}

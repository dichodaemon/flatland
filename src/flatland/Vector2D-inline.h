//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::x() const
{
 return _vector.x;
}

//------------------------------------------------------------------------------

inline
void
Flatland::Vector2D::x( double value )
{
  _vector.x = value;
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::y() const
{
  return _vector.y;
}

//------------------------------------------------------------------------------

inline
void
Flatland::Vector2D::y( double value )
{
  _vector.y = value;
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D &
Flatland::Vector2D::operator=( const Vector2D & other )
{
  if( this == &other )
  {
    return *this;
  }
  _vector = other._vector;
  return *this;
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D::operator const cpVect &() const
{
  return _vector;
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::operator+( const Vector2D & other ) const
{
  return cpvadd( _vector, other );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::operator-( const Vector2D & other ) const
{
  return cpvsub( _vector, other );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::operator-() const 
{
  return cpvneg( _vector );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::operator*( double other )
{
  return cpvmult( _vector, other );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::dot( const Vector2D & other )
{
  return cpvdot( _vector, other );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::cross( const Vector2D & other )
{
  return cpvcross( _vector, other );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::ccwPerpendicular()
{
  return cpvperp( _vector );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::cwPerpendicular()
{
  return cpvrperp( _vector );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::projection( const Vector2D & other )
{
  return cpvproject( _vector, other );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::ccwRotate( const Vector2D & other )
{
  return cpvrotate( _vector, other );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::cwRotate( const Vector2D & other )
{
  return cpvunrotate( _vector, other );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::length()
{
  return cpvlength( _vector );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::length2()
{
  return cpvlengthsq( _vector );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::lerp( const Vector2D & other, double t )
{
  return cpvlerp( _vector, other, t );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::slerp( const Vector2D & other, double t )
{
  return cpvslerp( _vector, other, t );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::clamp( double length )
{
  return cpvclamp( _vector, length );
}

//------------------------------------------------------------------------------

inline
Flatland::Vector2D
Flatland::Vector2D::normalize()
{
  return cpvnormalize( _vector );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::distance( const Vector2D & other )
{
  return cpvdist( _vector, other );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::distance2( const Vector2D & other )
{
  return cpvdistsq( _vector, other );
}

//------------------------------------------------------------------------------

inline
bool
Flatland::Vector2D::near( const Vector2D & other, double distance )
{
  return cpvnear( _vector, other, distance );
}

//------------------------------------------------------------------------------

inline
double
Flatland::Vector2D::angle()
{
  return cpvtoangle( _vector );
}

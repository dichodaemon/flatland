#include "Body.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Flatland::Body::Body( const Body & body )
  : _body( body._body )
{
}

//------------------------------------------------------------------------------

Flatland::Body::Body( double mass, double moment )
  : _owner( true )
{
  _body = cpBodyNew( mass, moment );
}

//------------------------------------------------------------------------------

Flatland::Body::Body( cpBody * body )
  : _owner( false )
{
  _body = body;
}

//------------------------------------------------------------------------------

Flatland::Body::operator cpBody *() const
{
  return _body;
}

//------------------------------------------------------------------------------

Flatland::Body::~Body()
{
  if ( _owner ) {
    cpBodyFree( _body );
  }
}

//------------------------------------------------------------------------------

double
Flatland::Body::mass()
{
  return cpBodyGetMass( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::mass( double value )
{
  return cpBodySetMass( _body, value );
}

//------------------------------------------------------------------------------

double
Flatland::Body::moment()
{
  return cpBodyGetMoment( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::moment( double value )
{
  return cpBodySetMoment( _body, value );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::position()
{
  return cpBodyGetPos( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::position( const Vector2D & value )
{
  return cpBodySetPos( _body, value );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::velocity()
{
  return cpBodyGetVel( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::velocity( const Vector2D & value )
{
  return cpBodySetVel( _body, value );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::force()
{
  return cpBodyGetForce( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::force( const Vector2D & value )
{
  return cpBodySetForce( _body, value );
}

//------------------------------------------------------------------------------

double
Flatland::Body::x() const
{
  return cpBodyGetPos( _body ).x;
}

//------------------------------------------------------------------------------

void
Flatland::Body::x( double value )
{
  Vector2D tmp = position();
  tmp.x( value );
  return cpBodySetPos( _body, tmp );
}

//------------------------------------------------------------------------------

double
Flatland::Body::y() const
{
  return cpBodyGetPos( _body ).y;
}

//------------------------------------------------------------------------------

void
Flatland::Body::y( double value )
{
  Vector2D tmp = position();
  tmp.y( value );
  return cpBodySetPos( _body, tmp );
}

//------------------------------------------------------------------------------

double
Flatland::Body::angle()
{
  return cpBodyGetAngle( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::angle( double value )
{
  return cpBodySetAngle( _body, value );
}

//------------------------------------------------------------------------------

double
Flatland::Body::angularVelocity()
{
  return cpBodyGetAngVel( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::angularVelocity( double value )
{
  return cpBodySetAngVel( _body, value );
}

//------------------------------------------------------------------------------

double
Flatland::Body::torque()
{
  return cpBodyGetTorque( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::torque( double value )
{
  return cpBodySetTorque( _body, value );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::rotation()
{
  return cpBodyGetRot( _body );
}

//------------------------------------------------------------------------------

void
Flatland::Body::applyForce( const Vector2D & magnitude, const Vector2D & offset )
{
  return cpBodyApplyForce( _body, magnitude, offset );
}

//------------------------------------------------------------------------------

void
Flatland::Body::applyImpulse( const Vector2D & magnitude, const Vector2D & offset )
{
  return cpBodyApplyImpulse( _body, magnitude, offset );
}

//------------------------------------------------------------------------------

void
Flatland::Body::resetForces()
{
  return cpBodyResetForces( _body );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::toWorld( const Vector2D & value )
{
  return cpBodyLocal2World( _body, value );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Body::toLocal( const Vector2D & value )
{
  return cpBodyWorld2Local( _body, value );
}

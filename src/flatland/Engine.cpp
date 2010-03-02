#include "Engine.h"
#include "Conversion.h"
#include "Constraint.h"
#include "Logger.h"
#include "Painter.h"
#include "Shape.h"

using namespace Flatland;
using namespace std;

//------------------------------------------------------------------------------

Flatland::Engine::Engine( const Configuration & configuration )
  : _configuration( configuration ),
    _bus(),
    _dispatcher( _bus ),
    _screen( configuration.getInt( "graphics", "width" ),
             configuration.getInt( "graphics", "height" ) ),
    _graphics( _screen ),
    _physicsPeriod( 1.0 / configuration.getDouble( "physics", "fps" ) ),
    _physicsRemainingTime( _physicsPeriod ),
    _fpsClock( configuration.getDouble( "graphics", "fps" ) ),
    _startTime( 0 ),
    _running( true )
{
}

//------------------------------------------------------------------------------

bool
Flatland::Engine::step( double delta )
{
  Logger::debug( "Step at time: " + toString( _fpsClock.seconds() ), "Engine" );
  bool result = handleEvents();
  if ( ! result ) {
    return false;
  }
  updatePhysics( delta );
  updateGraphics();
  return true;
}

//------------------------------------------------------------------------------

size_t
Flatland::Engine::run()
{
  while ( _running ) {
    double delta = _fpsClock.tick();
    Logger::debug( "Delta: " + toString( delta ) + ", Frequency: " + toString( 1.0 / delta ), "Engine" );
    if ( ! step( delta ) ) {
      break;
    }
  }
  return 0;
}

//------------------------------------------------------------------------------

void
Flatland::Engine::pause( bool value )
{
  _paused = value;
}

//------------------------------------------------------------------------------

bool
Flatland::Engine::pause()
{
  return _paused;
}

//------------------------------------------------------------------------------

void
Flatland::Engine::stop()
{
  _running = false;
}

//------------------------------------------------------------------------------

bool
Flatland::Engine::running()
{
  return _running;
}

//------------------------------------------------------------------------------

bool
Flatland::Engine::handleEvents()
{
  return _dispatcher.dispatch();
}

//------------------------------------------------------------------------------

void
Flatland::Engine::updateGraphics()
{
  _paintQueue.paint( _graphics );
  _screen.flip();
}

//------------------------------------------------------------------------------

void
Flatland::Engine::updatePhysics( double delta )
{
  _physicsRemainingTime += delta;
  while ( _physicsRemainingTime >= _physicsPeriod ) {
    _space.step( _physicsPeriod );
    _physicsRemainingTime -= _physicsPeriod;
  }
}

//------------------------------------------------------------------------------

void
Flatland::Engine::addPainter( Painter & painter, double depth )
{
  _paintQueue.addPainter( painter, depth );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::add( ChipmunkObject & object )
{
  if( Shape * shape = dynamic_cast< Shape * >( &object ) )
  {
    add( *shape );
  }
  else if ( Body * body = dynamic_cast< Body * >( &object ) )
  {
    add( *body );
  }
  else if ( Constraint * constraint = dynamic_cast< Constraint * >( &object ) )
  {
    add( *constraint );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Engine::add( Shape & shape )
{
  if ( shape.fixed() )
  {
    _space.addFixedShape( shape );
  }
  else
  {
    _space.addShape( shape );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Engine::add( Body & body )
{
  _space.addBody( body );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::add( Constraint & constraint )
{
  _space.addConstraint( constraint );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::remove( ChipmunkObject & object )
{
  if( Shape * shape = dynamic_cast< Shape * >( &object ) )
  {
    remove( *shape );
  }
  else if ( Body * body = dynamic_cast< Body * >( &object ) )
  {
    remove( *body );
  }
  else if ( Constraint * constraint = dynamic_cast< Constraint * >( &object ) )
  {
    remove( *constraint );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Engine::remove( Shape & shape )
{
  if ( shape.fixed() )
  {
    _space.removeFixedShape( shape );
  }
  else
  {
    _space.removeShape( shape );
  }
}

//------------------------------------------------------------------------------

void
Flatland::Engine::remove( Body & body )
{
  _space.removeBody( body );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::remove( Constraint & constraint )
{
  _space.removeConstraint( constraint );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::iterations( int value )
{
  _space.iterations( value );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::elasticIterations( int value )
{
  _space.elasticIterations( value );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::damping( double value )
{
  _space.damping( value );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::gravity( const Vector2D & g )
{
  _space.gravity( g );
}

//------------------------------------------------------------------------------

void
Flatland::Engine::setTransform( const Vector2D & center, double rotation, double width )
{
  _graphics.setTransform( center, rotation, width );
}

//------------------------------------------------------------------------------

double
Flatland::Engine::width()
{
  return _screen.width();
}

//------------------------------------------------------------------------------

double
Flatland::Engine::height()
{
  return _screen.height();
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Engine::toGraphics( const Vector2D & vector )
{
  return  _graphics.toGraphics( vector );
}

//------------------------------------------------------------------------------

Vector2D
Flatland::Engine::toWorld( const Vector2D & vector )
{
  return  _graphics.toWorld( vector );
}


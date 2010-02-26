#include <flatland/Body.h>
#include <flatland/CircleShape.h>
#include <flatland/Clock.h>
#include <flatland/Color.h>
#include <flatland/Configuration.h>
#include <flatland/Conversion.h>
#include <flatland/Engine.h>
#include "GameObject.h"
#include <flatland/GearJoint.h>
#include <flatland/KeyPressedEvent.h>
#include <flatland/KeyReleasedEvent.h>
#include <flatland/Logger.h>
#include <flatland/MouseDownEvent.h>
#include <flatland/MouseMovedEvent.h>
#include <flatland/MouseUpEvent.h>
#include <flatland/PinJoint.h>
#include <flatland/PivotJoint.h>
#include <flatland/PolygonShape.h>
#include <flatland/SegmentShape.h>
#include <flatland/SimpleMotor.h>
#include <flatland/SlideJoint.h>
#include <flatland/TypedEvent.h>
#include <iostream>
#include <deque>
#include <cmath>

using namespace std;
using namespace Flatland;

//------------------------------------------------------------------------------

class EventHandler
{
public:
  EventHandler( Engine & engine )
    : _engine( engine ),
      _applyForce( false )
  {
  }

  void onKeyPressed( const KeyPressedEvent & event ) {
    if ( event.key() == KeyboardEvent::KEY_ESCAPE ) {
      _engine.stop();
    }
  }

  void onMouseDown( const MouseDownEvent & event ) {
    switch ( event.button() ) {
      case MouseEvent::BUTTON_LEFT:
        _applyForce = true;
        break;
      default:
        break;
    }
  }

  void onMouseUp( const MouseUpEvent & event ) {
    switch ( event.button() ) {
      case MouseEvent::BUTTON_LEFT:
        _applyForce = false;
        break;
      default:
        break;
    }
  }

  void onMouseMoved( const MouseMovedEvent & event ) {
    double deltaT       = Clock::systemSeconds() - _lastSeconds;
    if ( deltaT > 0.05 )
    {
      Vector2D eventP( event.x(), event.y() );
      Vector2D deltaP = ( eventP - _lastP ) * ( 1.0 / ( 2000 ) );
      Vector2D v      = deltaP * ( 1.0 / deltaT );
      _lastA          = ( v - _lastV ) * ( 1.0 / deltaT );
      _lastP          = eventP;
      _lastSeconds    = _lastSeconds + deltaT;
      _lastV          = v;
    }
    if ( _applyForce )
    {
      Vector2D screen( Vector2D( event.x(), event.y() ) ) ;
      Vector2D world( _engine.toWorld( screen ) );
      _engine.send( "WHIP_POSE", TypedEvent<Vector2D>( world ) );
    }
  }

private:
  Engine & _engine;
  bool     _applyForce;
  Vector2D _lastP;
  double   _lastSeconds;
  Vector2D _lastV;
  Vector2D _lastA;
};

//------------------------------------------------------------------------------

class Whip : public GameObject
{
public:
  Whip( double x, double y, double length, double step )
    : _first( new Body( INFINITY, INFINITY ) ),
      _point( new Body( 0.5, 0.1 ) )
  {
    _body = new Body( INFINITY, INFINITY );
    _body->position( Vector2D( x, y ) );
    _first->position( Vector2D( x, y ) );
    
    _point->position( Vector2D( x, y + length * step ) );
    addObject( _point );

    CircleShape * s = new CircleShape( *_first, 0.1, Vector2D( 0, 0 ) );
    s->collisionGroup( 1 );
    s->friction( 1 );
    addObject( s );

    s = new CircleShape( *_body, 0.1, Vector2D( 0, -1 ) );
    s->friction( 1 );
    s->elasticity( 0 );
    addObject( s );


    Body * last    = _first;
    for ( int i = 1; i < length; ++i )
    {
      Body * body = new Body( 0.1, 0.1 );
      body->position( Vector2D( x, y + i * step ) );
      addObject( body );
      
      Constraint * c = new PivotJoint(
        *last, *body, Vector2D( x, y + ( i - 0.5 ) * step )
      );
      addObject( c );
      
      c = new SlideJoint(
        *_first, *body, Vector2D( 0, 0 ), Vector2D( 0, 0 ), 0.0, i * step
      );
      addObject( c );

      last = body;
    }


    Constraint * c = new PivotJoint(
      *last, *_point, Vector2D( x, y + ( length - 0.5 ) * step )
    );
    addObject( c );

    c = new SlideJoint(
      *_first, *_point, Vector2D( 0, 0 ), Vector2D( 0, 0 ), 0.0, length * step
    );
    addObject( c );

    s = new CircleShape( *_point, 0.1, Vector2D( 0, 0 ) );
    s->collisionGroup( 1 );
    s->friction( 1 );
    addObject( s );
  }

  virtual void paint( GraphicsContext & graphics )
  {
    GameObject::paint( graphics );
  }
  
  void onAcceleration( const TypedEvent<Vector2D> & event )
  {
    _first->position( _body->position() + ( event() - _body->position() ).normalize() * 0.50 );
  }
  
private:
  Body * _first;
  Body * _point;
};

//------------------------------------------------------------------------------

class Painters
{
public:
  void clear( GraphicsContext & graphics )
  {
    graphics.clear( Color( 0, 0, 0 ) );
  }
};

//------------------------------------------------------------------------------

int main( int argc, char * argv[] )
{
  if ( argc != 2 ) {
    Logger::error( "No configuration file was specified" , "main" );
    exit( 1 );
  }
  Configuration configuration( argv[1] );

  Engine engine( configuration );
  engine.gravity( Vector2D( 0, 9.81 ) );
  engine.elasticIterations( 5 );
  engine.damping( 1.0 );
  engine.iterations( 10 );
  
  engine.setTransform( Vector2D( 2, 2 ), 10 );

  EventHandler eventHandler( engine );

  Whip whip( 2, 2, 10, 0.2 );
  whip.addToEngine( engine );

  Painters painters;

  engine.subscribe( eventHandler, &EventHandler::onKeyPressed );
  engine.subscribe( eventHandler, &EventHandler::onMouseDown );
  engine.subscribe( eventHandler, &EventHandler::onMouseUp );
  engine.subscribe( eventHandler, &EventHandler::onMouseMoved );
  engine.subscribe( "WHIP_POSE", whip, &Whip::onAcceleration );
  
  engine.addPainter( painters, &Painters::clear );
  engine.addPainter( whip, &Whip::paint );

  engine.run();
}

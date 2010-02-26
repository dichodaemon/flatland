#include <flatland/Body.h>
#include <flatland/CircleShape.h>
#include <flatland/ClassLoader.h>
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
#include <algorithm>
#include <cmath>

using namespace std;
using namespace Flatland;

//------------------------------------------------------------------------------

class EventHandler
{
public:
  EventHandler( Engine & engine )
    : _engine( engine )
  {
    engine.subscribe( *this, &EventHandler::onKeyPressed );
    engine.subscribe( *this, &EventHandler::onMouseDown );
  }

  void onKeyPressed( const KeyPressedEvent & event ) {
    if ( event.key() == KeyboardEvent::KEY_ESCAPE ) {
      _engine.stop();
    }
  }

  void onMouseDown( const MouseDownEvent & event ) {
    Vector2D point = _engine.toWorld( Vector2D( event.x(), event.y() ) );
    switch ( event.button() ) {
      case MouseEvent::BUTTON_LEFT:
        _engine.send( "ROPE_TOGGLE", TypedEvent<Vector2D>( point ) );
        break;
      default:
        break;
    }
  }

private:
  Engine & _engine;
};

//------------------------------------------------------------------------------

class Painters
{
public:
  Painters( GameObject & object, double width, double lowerLimit )
    : _object( object ),
      _width( width ),
      _lowerLimit( lowerLimit )
  {
  }

  void center( GraphicsContext & graphics )
  {
    double x = _object.position().x();
    double y = std::min( _lowerLimit, _object.position().y() );
    graphics.setTransform( Vector2D( x, y ), _width );
  }

  void clear( GraphicsContext & graphics )
  {
    graphics.clear( Color( 0, 0, 0 ) );
  }

private:
  GameObject & _object;
  double       _width;
  double       _lowerLimit;
};

//------------------------------------------------------------------------------

class RopeMan : public GameObject
{
public:
  RopeMan( double x, double y, double mass, double width, double height )
  {
    _body = new Body( mass, mass * ( width * width + height * height ) / 12.0 );
    _body->position( Vector2D( x, y ) );
    addObject( _body );
    
    PolygonShape::VertexList square( 4 );
    square[0] = Vector2D( -width / 2, -height / 2 );
    square[1] = Vector2D( -width / 2,  height / 2 );
    square[2] = Vector2D(  width / 2,  height / 2 );
    square[3] = Vector2D(  width / 2, -height / 2 );

    PolygonShape * s = new PolygonShape( *_body, square, Vector2D( 0, 0 ) );
    s->collisionGroup( 1 );
    s->elasticity( 0.2 );
    s->friction( 1 );
    addObject( s );
  }

  Body & body()
  {
    return *_body;
  }
};

//------------------------------------------------------------------------------

class Floor : public GameObject
{
public:
  Floor( double x1, double y1, double x2, double y2, double thickness )
  {
    _body = new Body( INFINITY, INFINITY );
    _body->position( Vector2D( 0, 0 ) );
    
    SegmentShape * s = new SegmentShape(
      *_body, Vector2D( x1, y1 ), Vector2D( x2, y2 ), thickness, true
    );
    s->elasticity( 1 );
    s->friction( 1 );
    addObject( s );
  }

  ~Floor()
  {
    delete _body;
  }
};

//------------------------------------------------------------------------------

class Building : public GameObject
{
public:
  Building( double x, double width, double height )
  {
    _body = new Body( INFINITY, INFINITY );
    _body->position( Vector2D( 0, 0 ) );

    PolygonShape::VertexList square( 4 );
    square[0] = Vector2D( x, -height );
    square[1] = Vector2D( x,  0 );
    square[2] = Vector2D( x + width,  0 );
    square[3] = Vector2D( x + width, -height );

    PolygonShape * s = new PolygonShape( *_body, square, Vector2D( 0, 0 ), true );
    s->collisionGroup( 1 );
    addObject( s );
  }

  ~Building()
  {
    delete _body;
  }
};

//------------------------------------------------------------------------------

class Rope : public GameObject
{
public:
  Rope( RopeMan & ropeMan, double x, double y )
  {
    _body = new Body( INFINITY, INFINITY );
    _body->position( Vector2D( x, y ) );
    double distance = ropeMan.body().position().distance( _body->position() );

    SlideJoint * c = new SlideJoint(
      ropeMan.body(), *_body, Vector2D( 0, 0 ), Vector2D( 0, 0 ), 0, distance
    );
    addObject( c );
  }

  ~Rope()
  {
    delete _body;
  }
};

//------------------------------------------------------------------------------


class Level
{
public:
  Level( Engine & engine )
    : _engine( engine ),
      _floor( 0, 0, 3000, 0, 0.1 ),
      _ropeMan( 0, -100, 80, 0.4, 1.75 ),
      _rope( NULL ),
      _painters( _ropeMan, 100, -32 )
  {
    initialize();
  }

  virtual ~Level()
  {
    if ( _rope != NULL )
    {
      delete _rope;
    }
    Buildings::iterator i;
    Buildings::iterator iend = _buildings.end();
    for ( i = _buildings.begin(); i != iend; ++i )
    {
      delete *i;
    }
  }
  
  void initialize()
  {
    _engine.subscribe( "ROPE_TOGGLE", *this, &Level::onToggleRope );
    _engine.addPainter( _painters, &Painters::clear, -1E6 );
    _engine.addPainter( _painters, &Painters::center, -1E6 );
    add( _floor );

    double x = 20;

    for ( int i = 0; i < 100; ++i )
    {
      double width  = rand() % 20 + 10;
      double height = rand() % 40 + 60;
      double space  = rand() % 10 + 10;
      Building * b = new Building( x, width, height );
      x += width + space;
      _buildings.push_back( b );
      add( *b );
    }
    
    add( _ropeMan );
  }

  bool hitsBuilding( const Vector2D & vector )
  {
    Buildings::iterator i;
    Buildings::iterator iend = _buildings.end();
    for ( i = _buildings.begin(); i != iend; ++i )
    {
      if ( (*i)->contains( vector ) )
      {
        return true;
      }
    }
    return false;
  }

  void add( GameObject & object )
  {
    _engine.addPainter( object, &GameObject::paint );
    GameObject::ObjectList::iterator i;
    GameObject::ObjectList::iterator iend = object.objects().end();
    for ( i = object.objects().begin(); i != iend; ++i )
    {
      _engine.add( **i );
    }
  }
  
  void remove( GameObject & object )
  {
    _engine.removePainter( object, &GameObject::paint );
    GameObject::ObjectList::iterator i;
    GameObject::ObjectList::iterator iend = object.objects().end();
    for ( i = object.objects().begin(); i != iend; ++i )
    {
      _engine.remove( **i );
    }
  }
  
  void onToggleRope( const TypedEvent<Vector2D> & event )
  {
    Logger::debug( "Toggle rope", "Level" );
    if ( _rope == NULL )
    {
      Logger::debug( "Create rope", "Level" );
      if ( hitsBuilding( event() ) )
      {
        _rope = new Rope( _ropeMan, event().x(), event().y() );
        add( *_rope );
      }
    }
    else
    {
      Logger::debug( "Destroy rope", "Level" );
      remove( *_rope );
      delete _rope;
      _rope = NULL;
    }
  }

private:
  typedef deque<Building *> Buildings;
  
  Engine &  _engine;
  Floor     _floor;
  RopeMan   _ropeMan;
  Rope *    _rope;
  Buildings _buildings;

  Painters  _painters;
};

//------------------------------------------------------------------------------

int main( int argc, char * argv[] )
{
  if ( argc != 2 ) {
    Logger::error( "No configuration file was specified" , "main" );
    exit( 1 );
  }
  Configuration configuration( argv[1] );

  ClassLoader<ScreenBase>::searchPath(
    configuration.getString( "graphics", "libraryPath" )
  );
  ClassLoader<ScreenBase>::libraryName(
    configuration.getString( "graphics", "backend" )
  );
  ClassLoader<GraphicsContextBase>::searchPath(
    configuration.getString( "graphics", "libraryPath" )
  );
  ClassLoader<GraphicsContextBase>::libraryName(
    configuration.getString( "graphics", "backend" )
  );
  ClassLoader<EventDispatcherBase>::searchPath(
    configuration.getString( "eventSystem", "libraryPath" )
  );
  ClassLoader<EventDispatcherBase>::libraryName(
    configuration.getString( "eventSystem", "backend" )
  );

  Engine engine( configuration );
  engine.gravity( Vector2D( 0, 9.81 ) );
  engine.elasticIterations( 5 );
  engine.iterations( 10 );

  EventHandler eventHandler( engine );
  Level level( engine );

  engine.run();
}

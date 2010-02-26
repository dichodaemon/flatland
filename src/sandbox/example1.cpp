#include <flatland/Body.h>
#include <flatland/CircleShape.h>
#include <flatland/Color.h>
#include <flatland/Configuration.h>
#include <flatland/Conversion.h>
#include <flatland/Engine.h>
#include <flatland/GearJoint.h>
#include <flatland/KeyPressedEvent.h>
#include <flatland/KeyReleasedEvent.h>
#include <flatland/Logger.h>
#include <flatland/MouseDownEvent.h>
#include <flatland/MouseMovedEvent.h>
#include <flatland/MouseUpEvent.h>
#include <flatland/PinJoint.h>
#include <flatland/PolygonShape.h>
#include <flatland/SegmentShape.h>
#include <flatland/SimpleMotor.h>
#include <flatland/SlideJoint.h>
#include <iostream>
#include <deque>
#include <cmath>

using namespace std;
using namespace Flatland;

typedef deque< ChipmunkObject * > PhysicsObjectList;

//------------------------------------------------------------------------------

class PhysicsPainter
{
public:

  virtual ~PhysicsPainter() {
    PhysicsObjectList::iterator i;
    PhysicsObjectList::iterator iend = _objects.end();
    for ( i = _objects.begin(); i != iend; ++i )
    {
      delete *i;
    }
  }
  
  void addObject( ChipmunkObject * object )
  {
    _objects.push_back( object );
  }

  void paint( GraphicsContext & graphics )
  {
    PhysicsObjectList::iterator i;
    PhysicsObjectList::iterator iend = _objects.end();
    for ( i = _objects.begin(); i != iend; ++i )
    {
      if( CircleShape * circle = dynamic_cast< CircleShape * >( *i ) )
      {
        paint( graphics, *circle );
      }
      else if ( SegmentShape * segment = dynamic_cast< SegmentShape * >( *i ) )
      {
        paint( graphics, *segment );
      }
      else if ( PolygonShape * polygon = dynamic_cast< PolygonShape * >( *i ) )
      {
        paint( graphics, *polygon );
      }
      else if ( Body * body = dynamic_cast< Body * >( *i ) )
      {
        paint( graphics, *body );
      }
      else if ( Constraint * constraint = dynamic_cast< Constraint * >( *i ) )
      {
        paint( graphics, *constraint );
      }
    }
  }

  void paint( GraphicsContext & graphics, Body & body )
  {
    graphics.fillCircle( body.x(), body.y(), 5, Color( 0, 0, 255 ) );
    graphics.drawCircle( body.x(), body.y(), 5, Color( 100, 100, 100 ) );
  }

  void paint( GraphicsContext & graphics, CircleShape & circle )
  {
    Vector2D center = circle.worldOffset();
    graphics.drawCircle(
      center.x(), center.y(), circle.radius(), Color( 255, 255, 255 )
    );
  }

  void paint( GraphicsContext & graphics, SegmentShape & segment )
  {
    Vector2D v1 = segment.worldV1();
    Vector2D v2 = segment.worldV2();
    graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 255 ) );
  }

  void paint( GraphicsContext & graphics, PolygonShape & polygon )
  {
    for ( int i = 0; i < polygon.size(); ++i )
    {
      Vector2D v1 = polygon.body().toWorld( polygon.vertex( i ) );
      Vector2D v2 = polygon.body().toWorld( polygon.vertex( ( i + 1 ) % polygon.size() ) );
      graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 255 ) );
    }
  }

  void paint( GraphicsContext & graphics, Constraint & constraint )
  {
    Vector2D v1 = constraint.body1().position();
    Vector2D v2 = constraint.body2().position();
    graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 0 ) );
  }


private:
  PhysicsObjectList _objects;
};


//------------------------------------------------------------------------------

class EventHandler
{
public:
  EventHandler( Engine & engine, PhysicsPainter & pp )
    : _engine( engine ),
      _pp( pp )
  {
    addLimits();
  }

  void motor( SimpleMotor * motor )
  {
    _motor = motor;
  }

  void onKeyPressed( const KeyPressedEvent & event ) {
    if ( event.key() == KeyboardEvent::KEY_ESCAPE ) {
      _engine.stop();
    }
    else if ( event.key() == KeyboardEvent::KEY_c ) {
      addCircles();
    }
    else if ( event.key() == KeyboardEvent::KEY_q ) {
      addSquares();
    }
    else if ( event.key() == KeyboardEvent::KEY_p ) {
      addPile();
    }
    else if ( event.key() == KeyboardEvent::KEY_o ) {
      addBomb();
    }
    else if ( event.key() == KeyboardEvent::KEY_s ) {
      addSurface();
    }
    else if ( event.key() == KeyboardEvent::KEY_v ) {
      addVehicle();
    }
    else if ( event.key() == KeyboardEvent::KEY_b ) {
      addBubble();
    }
    else {
      Logger::info( "Key Pressed: " + toString( event.key() ), "main" );
    }
  }

  void onKeyReleased( const KeyReleasedEvent & event ) {
    Logger::info( "Key Released: " + toString( event.key() ), "main" );
  }

  void onMouseDown( const MouseDownEvent & event ) {
    Logger::info(
      "Mouse button pressed: " +
      toString( event.x() ) + ", " + toString( event.y() ), "main"
    );
    switch ( event.button() ) {
      case MouseEvent::BUTTON_LEFT:
        _motor->rate( 1 * 2 * M_PI );
        break;
      case MouseEvent::BUTTON_RIGHT:
        _motor->rate( -1 * 2 * M_PI );
        break;
      default:
      case MouseEvent::BUTTON_MIDDLE:
        _motor->rate( 0 );
        break;
    }
  }

  void onMouseUp( const MouseUpEvent & event ) {
    Logger::info(
      "Mouse button released: " +
      toString( event.x() ) + ", " + toString( event.y() ), "main"
    );
  }

  void onMouseMoved( const MouseMovedEvent & event ) {
    _x = event.x();
    _y = event.y();
  }

  void drawMousePosition( GraphicsContext & graphics ) {
    graphics.clear( Color( 0, 0, 0 ) );
    graphics.fillCircle( _x, _y, 60, Color( 0x80, 0x80, 0x80, 0x80 ) );
    graphics.drawCircle( _x, _y, 60, Color( 255, 255, 255 ) );
  }

  void addLimits()
  {
    _floorBody = new Body( INFINITY, INFINITY );
    _floorBody->position( Vector2D( 0, 0 ) );
    _pp.addObject( _floorBody );

    SegmentShape * floorShape = new SegmentShape( *_floorBody, Vector2D( 0, 511 ), Vector2D( 511, 511 ), 1 );
    floorShape->friction( 0.9 );
    floorShape->elasticity( 0 );
    _pp.addObject( floorShape );
    _engine.addStaticShape( *floorShape );

//     floorShape = new SegmentShape( *_floorBody, Vector2D( 0, 0 ), Vector2D( 511, 0 ), 1 );
//     floorShape->friction( 0.9 );
//     floorShape->elasticity( 0 );
//     _pp.addObject( floorShape );
//     _engine.addStaticShape( *floorShape );

    floorShape = new SegmentShape( *_floorBody, Vector2D( 0, 511 ), Vector2D( 0, 100 ), 1 );
    floorShape->friction( 0.9 );
    floorShape->elasticity( 0 );
    _pp.addObject( floorShape );
    _engine.addStaticShape( *floorShape );

    floorShape = new SegmentShape( *_floorBody, Vector2D( 511, 511  ), Vector2D( 511, 100 ), 1 );
    floorShape->friction( 0.9 );
    floorShape->elasticity( 0 );
    _pp.addObject( floorShape );
    _engine.addStaticShape( *floorShape );
  }

  void addCircles()
  {
    for ( size_t i = 0; i < 100; ++i )
    {
      Body * b = new Body( 1, 1 );
      b->position( Vector2D( rand() % 512, rand() % 105 + 406 ) );
      _pp.addObject( b );
      _engine.addBody( *b );

      CircleShape * c = new CircleShape( *b, 10, Vector2D( 0, 0 ) );
      c->elasticity( 0 );
      c->friction( 0.9 );
      _pp.addObject( c );
      _engine.addShape( *c );
    }
  }

  void addSquares()
  {
    PolygonShape::VertexList square( 4 );
    square[0] = Vector2D( -10, -10 );
    square[1] = Vector2D( -10,  10 );
    square[2] = Vector2D(  10,  10 );
    square[3] = Vector2D(  10, -10 );
    for ( size_t i = 0; i < 100; ++i )
    {
      Body * b = new Body( 1, 1 );
      b->position( Vector2D( rand() % 512, rand() % 105 + 406 ) );
      _pp.addObject( b );
      _engine.addBody( *b );

      PolygonShape * p = new PolygonShape( *b, square, Vector2D( 0, 0 ) );
      p->elasticity( 0 );
      p->friction( 0.9 );
      _pp.addObject( p );
      _engine.addShape( *p );
      
    }
  }

  void addBubble()
  {
    Body * b1 = new Body( 1, 1 );
    b1->position( Vector2D( 350, 150 ) );
    _pp.addObject( b1 );
    _engine.addBody( *b1 );

    CircleShape * c = new CircleShape( *b1, 200, Vector2D( 0, 0 ) );
    c->elasticity( 0 );
    c->friction( 0.9 );
    _pp.addObject( c );
    _engine.addShape( *c );
  }

  void addPile()
  {

    double startX = 0;
    double startY = 511;
    double delta  = 40;
    double height = 3;
    double width  = 12;

    PolygonShape::VertexList square( 4 );
    square[0] = Vector2D( -delta / 2, -delta / 2 );
    square[1] = Vector2D( -delta / 2,  delta / 2 );
    square[2] = Vector2D(  delta / 2,  delta / 2 );
    square[3] = Vector2D(  delta / 2, -delta / 2 );


    for ( int x = 0; x < width; ++x )
    {
      for ( int y = 0; y < height; ++y )
      {
        Body * b1 = new Body( 10, 10 );
        b1->position( Vector2D( x * delta + delta / 2 + startX, -y * delta - delta / 2 + startY ) );
        _pp.addObject( b1 );
        _engine.addBody( *b1 );

        CircleShape * c = new CircleShape( *b1, delta / 2.0, Vector2D( 0, 0 ) );
        c->elasticity( 0 );
        c->friction( 1 );
        _pp.addObject( c );
        _engine.addShape( *c );
/*        PolygonShape * c = new PolygonShape( *b1, square, Vector2D( 0, 0 ) );
        c->elasticity( 0 );
        c->friction( 1 );
        _pp.addObject( c );
        _engine.addShape( *c );*/
      }
    }
  }
  
  void addBomb()
  {
    Body * b1 = new Body( 1, 1 );
    b1->position( Vector2D( 250, 550 ) );
    b1->force( Vector2D( 0, -30000 ) );
    _pp.addObject( b1 );
    _engine.addBody( *b1 );

    SimpleMotor * _motor = new SimpleMotor( *_floorBody, *b1, 0 );
    _engine.addConstraint( *_motor );
    _pp.addObject( _motor );

    SegmentShape * c = new SegmentShape( *b1, Vector2D( -50, 25 ), Vector2D( 0, 50 ), 1 );
    c->collisionGroup( 1 );
    c->elasticity( 0 );
    c->friction( 0.9 );
    _pp.addObject( c );
    _engine.addShape( *c );

    c = new SegmentShape( *b1, Vector2D( 50, 25 ), Vector2D( 0, 50 ), 1 );
    c->collisionGroup( 1 );
    c->elasticity( 0 );
    c->friction( 0.9 );
    _pp.addObject( c );
    _engine.addShape( *c );
  }
  
  void addSurface()
  {
    int countSegments = 60;
    double increment  = 512.0 / ( countSegments - 1 );
    Body * last  = NULL;
    Body * first = NULL;
    for ( int i = 1; i < countSegments -1; ++i )
    {
      Body * b1 = new Body( 1, 1 );
      b1->position( Vector2D( i * increment, 300 ) );
      _pp.addObject( b1 );
      _engine.addBody( *b1 );

      if ( first == NULL )
      {
        first = b1;
      }

      CircleShape * c = new CircleShape( *b1, increment / 2.0, Vector2D( 0, 0 ) );
      c->elasticity( 0 );
      c->friction( 1 );
      c->collisionGroup( 2 );
      _pp.addObject( c );
      _engine.addShape( *c );


      if ( last != NULL ) {
        Constraint * joint = new SlideJoint(
          *last, *b1,
          Vector2D( 0, 0 ), Vector2D( 0, 0 ),
          0.5 * increment, 1.1 * increment
        );
        joint->maxForce( 1000000 );
        _pp.addObject( joint );
        _engine.addConstraint( *joint );
      }
      last = b1;
    }
    Constraint * extremes = new SlideJoint(
      *last, *_floorBody,
      Vector2D( 0, 0 ), Vector2D( 512, 300 ),
      0.9 * increment, 1.1 * increment
    );
    _pp.addObject( extremes );
    _engine.addConstraint( *extremes );
    extremes = new SlideJoint(
      *first, *_floorBody,
      Vector2D( 0, 0 ), Vector2D( 0, 300 ),
      0.9 * increment, 1.1 * increment
    );
    _pp.addObject( extremes );
    _engine.addConstraint( *extremes );
  }

  void addVehicle()
  {
    Body * b1 = new Body( 10, 1 );
    b1->position( Vector2D( 300, 150 ) );
    _pp.addObject( b1 );
    _engine.addBody( *b1 );

    CircleShape * c = new CircleShape( *b1, 25, Vector2D( 0, 0 ) );
    c->collisionGroup( 1 );
    c->elasticity( 0 );
    c->friction( 1 );
    _pp.addObject( c );
    _engine.addShape( *c );

    Body * b2 = new Body( 10, 1 );
    b2->position( b1->position() + Vector2D( 100, 0 ) );
    _pp.addObject( b2 );
    _engine.addBody( *b2 );

    c = new CircleShape( *b2, 25, Vector2D( 0, 0 ) );
    c->collisionGroup( 1 );
    c->elasticity( 0 );
    c->friction( 1 );
    _pp.addObject( c );
    _engine.addShape( *c );

    Body * b3 = new Body( 10, 1 );
    b3->position( b1->position() + Vector2D( 50, 0 ) );
    _pp.addObject( b3 );
    _engine.addBody( *b3 );

//     c = new CircleShape( *b3, 25, Vector2D( 0, 0 ) );
//     c->collisionGroup( 1 );
//     c->elasticity( 0 );
//     c->friction( 0.9 );
//     _pp.addObject( c );
//     _engine.addShape( *c );


//     SegmentShape * s = new SegmentShape( *b3, Vector2D( -50, 20 ), Vector2D( 50, 20 ), 3 );
//     s->collisionGroup( 1 );
//     s->elasticity( 0 );
//     s->friction( 0 );
//     _pp.addObject( s );
//     _engine.addShape( *s );

    Body * b0 = new Body( 10, 1 );
    b0->position( b1->position() + Vector2D( 50, 50 ) );
    _pp.addObject( b0 );
    _engine.addBody( *b0 );

    Constraint * joint = new PinJoint( *b1, *b2, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );

    joint = new PinJoint( *b0, *b1, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );

    joint = new PinJoint( *b0, *b2, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );

    joint = new PinJoint( *b2, *b3, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );

    joint = new PinJoint( *b0, *b3, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );

    _motor = new SimpleMotor( *_floorBody, *b1, 0 );
//     _motor->maxForce( 500000 );
    _engine.addConstraint( *_motor );
    _pp.addObject( _motor );

    joint = new GearJoint( *b1, *b2, 1, 0 );
    _engine.addConstraint( *joint );
    _pp.addObject( joint );
  }

private:
  Engine &         _engine;
  PhysicsPainter & _pp;
  int              _x;
  int              _y;
  Body *           _floorBody;
  SimpleMotor *    _motor;
};

//------------------------------------------------------------------------------


class Vehicle
{
public:
  Vehicle(
    const Vector2D & position,
    double wheelDistance,
    double wheelRadius,
    double wheelmass,
    double balanceDistance,
    double balanceWeight,
    double maxForce,
    double bodyHeight,
    double bodyWeight
  )
  {
    PolygonShape::VertexList square( 4 );
    double d = wheelDistance + wheelRadius;
    square[0] = Vector2D( -d, -d );
    square[1] = Vector2D( -d,  d );
    square[2] = Vector2D(  d,  d );
    square[3] = Vector2D(  d, -d );
    
    _body = new Body( bodyWeight, bodyWeight );
    _body->position( position );
    addObject( _body );

    PolygonShape * polygon = new PolygonShape( *_body, square, Vector2D( 0, 0 ) );
    addObject( polygon );
    
    _motorBody = new Body( bodyWeight, bodyWeight );
    _motorBody->position( position );
    addObject( _motorBody );
    
    _motor = new SimpleMotor( staticBody(), *_motorBody, 0 );
    _motor->maxForce( maxForce );
    addObject( _motor );

    PinJoint * pin = new PinJoint( *_body, *_motorBody, Vector2D( 0, 0 ), Vector2D( 0, 0 ) );
    addObject( pin );

    
  }

  void addObject( ChipmunkObject * object )
  {
    _objects.push_back( object );
  }
  
protected:
  static Body _staticBody;
  
  static Body & staticBody()
  {
    return  _staticBody;
  }

  

private:
  PhysicsObjectList  _objects;
  Body *             _body;
  Body *             _motorBody;
  SimpleMotor *      _motor;
};

Body Vehicle::_staticBody( INFINITY, INFINITY );

//------------------------------------------------------------------------------

int main( int argc, char * argv[] )
{
  if ( argc != 2 ) {
    Logger::error( "No configuration file was specified" , "main" );
    exit( 1 );
  }
  Configuration configuration( argv[1] );
  
  Engine engine( configuration );
  engine.gravity( Vector2D( 0, 98.1 ) );
  
  PhysicsPainter pp;
  EventHandler eventHandler( engine, pp );
  
  engine.subscribe( eventHandler, &EventHandler::onKeyPressed );
  engine.subscribe( eventHandler, &EventHandler::onKeyReleased );
  engine.subscribe( eventHandler, &EventHandler::onMouseDown );
  engine.subscribe( eventHandler, &EventHandler::onMouseUp );
  engine.subscribe( eventHandler, &EventHandler::onMouseMoved );
  engine.addPainter( eventHandler, &EventHandler::drawMousePosition );
  engine.addPainter( pp, &PhysicsPainter::paint );

  engine.run();
}

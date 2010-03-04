#ifndef FLATLAND_ENGINE_H
#define FLATLAND_ENGINE_H


#include "Bus.h"
#include "Clock.h"
#include "Configuration.h"
#include "GraphicsContext.h"
#include "PaintQueue.h"
#include "Space.h"
#include "StandardEvents.h"
#include "Vector2D.h"
#include "Window.h"
#include <cstdlib>


namespace Flatland
{


class Painter;


class Engine
{
public:
  /**
   * Initializes the engine according to the given configuration.
   */
  Engine( const Configuration & configuration );
  
  /**
   * Executes a single world step of the engine.
   *
   * @param delta Time elapsed since last step.
   * @return True while the engine is running.
   */
  bool step( double delta );

  /**
   * Enters the game loop.
   *
   * @return Exit code.
   */
  size_t run();

  /**
   * Pauses/unpauses the engine.
   *
   * @param value True = paused, False = running.
   */
  void pause( bool value );

  /**
   * Returns the pause status of the engine.
   */
  bool pause();

  /**
   * Stops the engine.
   *
   */
  void stop();

  /**
   * Returns the pause status of the engine.
   */
  bool running();

  /**
   * Subscribes to an event.
   *
   * @param object Handling object.
   * @param handler Handling method.
   */
  template < class T, class EVENT >
  void subscribe( T & object, void ( T::*handler )( EVENT& ) );

  template < class EVENT >
  void send( const EVENT & event );

  template < class EVENT >
  void send( const std::string & name, const EVENT & event );

  template < class T, class EVENT >
  void subscribe(
    const std::string & name,
    T & object,
    void ( T::*handler )( EVENT& )
  );

  /**
   * Adds a painter to the paint queue.
   *
   * @param painter Painter object.
   */
  void addPainter( Painter & painter, double depth = 0 );

  /**
   * Adds a painter to the paint queue.
   *
   * @param object object.
   * @param handler paint method.
   */
  template < class T >
  void addPainter( T & instance, void (T::*method)( GraphicsContext & ), double depth = 0 );

  /**
   * Removes a painter from the paint queue.
   *
   * @param painter Painter object.
   */
  void removePainter( Painter & painter );

  /**
   * Removes a painter from the paint queue.
   *
   * @param object object.
   * @param handler paint method.
   */
  template < class T >
  void removePainter( T & instance, void (T::*method)( GraphicsContext & ) );

  void add( ChipmunkObject & object );
  void add( Shape & shape );
  void add( Body & body );
  void add( Constraint & constraint );

  void remove( ChipmunkObject & object );
  void remove( Shape & shape );
  void remove( Body & body );
  void remove( Constraint & constraint );

  void iterations( int value );

  void elasticIterations( int value );

  void damping( double value );

  void gravity( const Vector2D & g );

  void onProcessFrame( const UpdateEvent & );
  
  void setTransform( const Vector2D & center, double rotation, double width );
  double width();
  double height();
  Vector2D toGraphics( const Vector2D & vector );
  Vector2D toWorld( const Vector2D & vector );

protected:
  void updatePhysics( double delta );
  void updateGraphics();

private:
  const Configuration & _configuration;
  Bus                   _bus;
  Window                _window;
  GraphicsContext       _graphics;
  PaintQueue            _paintQueue;
  Space                 _space;
  double                _physicsPeriod;
  double                _physicsRemainingTime;
  double                _fps;
  Clock                 _fpsClock;
  bool                  _paused;
  double                _startTime;
  bool                  _running;

};


}


#include "Engine.tpp"


#endif //FLATLAND_ENGINE_H
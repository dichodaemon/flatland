#ifndef FLATLAND_GAME_OBJECT_H
#define FLATLAND_GAME_OBJECT_H


#include <flatland/Vector2D.h>
#include <deque>


namespace Flatland
{


class Body;
class Engine;
class GraphicsContext;


class GameObject
{
public:
  typedef std::deque< ChipmunkObject * > ObjectList;

  virtual ~GameObject();
  
  Vector2D position();
  
  void position( const Vector2D & value );

  virtual void paint( GraphicsContext & graphics );

  virtual bool contains( const Vector2D & value );

  ObjectList & objects();

protected:
  void addObject( ChipmunkObject * object );

protected:
  Body *      _body;
private:
  ObjectList  _objects;
};


}


#endif //FLATLAND_GAME_OBJECT_H
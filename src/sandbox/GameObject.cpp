#include "GameObject.h"
#include "ChipmunkPainter.h"
#include <flatland/Body.h>
#include <flatland/Constraint.h>
#include <flatland/Engine.h>
#include <flatland/GraphicsContext.h>
#include <flatland/Shape.h>

//------------------------------------------------------------------------------

Flatland::GameObject::~GameObject()
{
  ObjectList::iterator i;
  ObjectList::iterator iend = _objects.end();
  for ( i = _objects.begin(); i != iend; ++i )
  {
    delete *i;
  }
}

//------------------------------------------------------------------------------

Flatland::Vector2D
Flatland::GameObject::position()
{
  return _body->position();
}

//------------------------------------------------------------------------------

void
Flatland::GameObject::position( const Vector2D & value )
{
  _body->position( value );
}

//------------------------------------------------------------------------------

Flatland::GameObject::ObjectList &
Flatland::GameObject::objects()
{
  return _objects;
}

//------------------------------------------------------------------------------

bool
Flatland::GameObject::contains( const Vector2D & value )
{
  ObjectList::iterator i;
  ObjectList::iterator iend = _objects.end();
  for ( i = _objects.begin(); i != iend; ++i )
  {
    if( Shape * shape = dynamic_cast< Shape * >( *i ) )
    {
      if ( shape->contains( value ) )
      {
        return true;
      }
    }
  }
  return false;
}

//------------------------------------------------------------------------------

void
Flatland::GameObject::addObject( ChipmunkObject * object )
{
  _objects.push_back( object );
}

//------------------------------------------------------------------------------

void
Flatland::GameObject::paint( GraphicsContext & graphics )
{
  ObjectList::iterator i;
  ObjectList::iterator iend = _objects.end();
  for ( i = _objects.begin(); i != iend; ++i )
  {
    ChipmunkPainter::paint( graphics, **i );
  }
}

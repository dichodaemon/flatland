#include "EventDispatcher.h"
#include <flatland/Bus.h>
#include <flatland/KeyPressedEvent.h>
#include <flatland/KeyReleasedEvent.h>
#include <flatland/MouseDownEvent.h>
#include <flatland/MouseUpEvent.h>
#include <flatland/MouseMovedEvent.h>

using namespace Flatland;

//------------------------------------------------------------------------------

MouseEvent::Button convertSDLButton( int button )
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
      return MouseEvent::BUTTON_LEFT;
    case SDL_BUTTON_MIDDLE:
      return MouseEvent::BUTTON_MIDDLE;
    default:
      return MouseEvent::BUTTON_RIGHT;
  }
}

//------------------------------------------------------------------------------

EventDispatcher::EventDispatcher( Bus & bus )
  : _bus( bus )
{
}

//------------------------------------------------------------------------------

bool
EventDispatcher::dispatch()
{
  SDL_Event event;
  while( SDL_PollEvent( &event ) ) {
    switch ( event.type )
    {
      case SDL_QUIT:
        return false;
      case SDL_KEYDOWN:
        _bus.send( KeyPressedEvent( static_cast<Flatland::KeyboardEvent::Keys>( event.key.keysym.sym ) ) );
        break;
      case SDL_KEYUP:
        _bus.send( KeyReleasedEvent( static_cast<Flatland::KeyboardEvent::Keys>( event.key.keysym.sym ) ) );
        break;
      case SDL_MOUSEBUTTONDOWN:
        _bus.send( MouseDownEvent(
          event.button.x, event.button.y, convertSDLButton( event.button.button )
        ) );
        break;
      case SDL_MOUSEBUTTONUP:
        _bus.send( MouseUpEvent(
          event.button.x, event.button.y, convertSDLButton( event.button.button )
        ) );
        break;
      case SDL_MOUSEMOTION:
        _bus.send( MouseMovedEvent( event.button.x, event.button.y ) );
        break;
    }
  }
  return true;
}

//------------------------------------------------------------------------------

Flatland::EventDispatcherBase *
newEventDispatcher( Flatland::Bus & bus )
{
  return new EventDispatcher( bus );
}
#include "CocoaObject.h"
#include <flatland/Logger.h>

using namespace Flatland;

NSAutoreleasePool * CocoaObject::_pool = NULL;

//------------------------------------------------------------------------------

size_t CocoaObject::_references = 0;

//------------------------------------------------------------------------------

@interface NSApplication( SDL_Missing_Methods )
- (void) setAppleMenu:( NSMenu * ) menu;
@end

//------------------------------------------------------------------------------

@interface NSApplication (SDLApplication)
@end

@implementation NSApplication (SDLApplication)
/* Invoked from the Quit menu item */
- (void)terminate:(id)sender
{
    // /* Post a SDL_QUIT event */
    // SDL_Event event;
    // event.type = SDL_QUIT;
    // SDL_PushEvent(&event);
}
@end

//------------------------------------------------------------------------------

CocoaObject::CocoaObject()
{
  if ( _references == 0 ) {
    Logger::info( "Initializing Cocoa", "COCOA" );
    _pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
  }
  _references++;
}

//------------------------------------------------------------------------------

CocoaObject::~CocoaObject()
{
  _references--;
  if ( _references == 0 ) {
    Logger::info( "Quitting COCOA", "COCOA" );
    [_pool release];
  }
}

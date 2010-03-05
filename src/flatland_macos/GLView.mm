#import "GLView.h"
#import "KeyMap.h"
#include <flatland/Conversion.h>
#include <flatland/KeyPressedEvent.h>
#include <flatland/KeyReleasedEvent.h>
#include <flatland/Logger.h>
#include <flatland/MouseDownEvent.h>
#include <flatland/MouseMovedEvent.h>
#include <flatland/MouseUpEvent.h>

using namespace Flatland;

@implementation GLView

//------------------------------------------------------------------------------

- (void) toggleFullScreen
{
}

//------------------------------------------------------------------------------

- (id) initWithFrame: (NSRect) frameRect andBus: (Flatland::Bus*) bus
{
  // [[self openGLContext] flushBuffer];
  NSOpenGLPixelFormat *nsglFormat;

  NSOpenGLPixelFormatAttribute attr[] = 
  {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFAColorSize, 32,
    NSOpenGLPFADepthSize, 32,
    0 
  };

  // [self setPostsFrameChangedNotifications: YES];

  nsglFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes: attr];

  if ( ! nsglFormat ) { 
    Flatland::Logger::error( "Invalid format", "COCOA_VIEW" ); 
    return nil; 
  }

  self = [super initWithFrame: frameRect pixelFormat: nsglFormat];
  [nsglFormat release];

  if ( !self ) { 
    Flatland::Logger::error( "Self is null", "COCOA_VIEW" ); 
    return nil;
  }
  _bus = bus;

  [[self openGLContext] makeCurrentContext];

  return self;
}

//------------------------------------------------------------------------------

- (void) keyDown:(NSEvent *)theEvent
{
  _bus->send( KeyPressedEvent( toKeys( theEvent.keyCode ) ) );
}

//------------------------------------------------------------------------------

- (void) keyUp:(NSEvent *)theEvent
{
  _bus->send( KeyReleasedEvent( toKeys( theEvent.keyCode ) ) );
}

//------------------------------------------------------------------------------

- (void) mouseUp:(NSEvent *)theEvent
{
    NSPoint pt = [theEvent locationInWindow];
    NSRect r = [self bounds];
    pt.x = pt.x - r.size.width / 2.0;
    pt.y = pt.y - r.size.height / 2.0;
    _bus->send( MouseUpEvent(
      pt.x, pt.y, MouseEvent::BUTTON_LEFT
    ) );
}

//------------------------------------------------------------------------------

- (void) mouseDown:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseDownEvent(
    pt.x, pt.y, MouseEvent::BUTTON_LEFT
  ) );
}

//------------------------------------------------------------------------------

- (void) mouseMoved:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseMovedEvent(
    pt.x, pt.y
  ) );
}

//------------------------------------------------------------------------------

- (void) rightMouseUp:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseUpEvent(
    pt.x, pt.y, MouseEvent::BUTTON_RIGHT
  ) );
}

//------------------------------------------------------------------------------

- (void) rightMouseDown:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseDownEvent(
    pt.x, pt.y, MouseEvent::BUTTON_RIGHT
  ) );
}

//------------------------------------------------------------------------------

- (void) otherMouseUp:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseUpEvent(
    pt.x, pt.y, MouseEvent::BUTTON_MIDDLE
  ) );
}

//------------------------------------------------------------------------------

- (void) otherMouseDown:(NSEvent *)theEvent
{
  NSPoint pt = [theEvent locationInWindow];
  pt.y = [self bounds].size.height - pt.y;
  _bus->send( MouseDownEvent(
    pt.x, pt.y, MouseEvent::BUTTON_MIDDLE
  ) );
}

//------------------------------------------------------------------------------

@end
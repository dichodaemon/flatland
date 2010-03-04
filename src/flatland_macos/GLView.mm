#import "GLView.h"
#include <flatland/Logger.h>

@implementation GLView

//------------------------------------------------------------------------------

- (void) toggleFullScreen
{
}

//------------------------------------------------------------------------------

- (id) initWithFrame: (NSRect) frameRect
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

  [[self openGLContext] makeCurrentContext];

  return self;
}

//------------------------------------------------------------------------------

@end
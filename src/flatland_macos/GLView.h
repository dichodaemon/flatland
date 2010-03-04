#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView

{
  bool        fullScreen;
  NSWindow    *window;

}

- (void) toggleFullScreen;
- (id) initWithFrame: (NSRect) frameRect;

@end

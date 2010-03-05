#include <flatland/Bus.h>
#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView

{
  bool        fullScreen;
  Flatland::Bus * _bus;  
}

- (void) toggleFullScreen;
- (id) initWithFrame: (NSRect) frameRect andBus: (Flatland::Bus*) bus;

@end

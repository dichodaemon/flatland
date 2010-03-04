#import "GLView.h"
#include <Flatland/Bus.h>

@interface ApplicationDelegate : NSObject
{
  Flatland::Bus * _bus;
  double          _width;
  double          _height;
  double          _fps;
  NSTimer *       _updateTimer;
  NSWindow *      _window;
  GLView *        _view;
}

- (id)  initWithBus: (Flatland::Bus*) bus 
        andWidth: (double) width 
        andHeight: (double) height
        andFps: (double) fps;
- (void) flip; 
- (void) onUpdate:(id) sender;
- (void) run;
@end

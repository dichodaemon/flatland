#import "ApplicationDelegate.h"
#include <flatland/StandardEvents.h>
#include <flatland/Logger.h>

//------------------------------------------------------------------------------

@interface NSApplication( MissingMethods )
- (void) setAppleMenu:( NSMenu * ) menu;
@end

@implementation NSApplication ( FlatlandAdditions )
- (void)terminate:(id)sender
{
  [self stop: sender];
  Flatland::Logger::info( "Got termination signal", "COCOA" );
}
@end

//------------------------------------------------------------------------------

@implementation ApplicationDelegate

//------------------------------------------------------------------------------

- (id)  initWithBus: (Flatland::Bus*) bus 
        andWidth: (double) width 
        andHeight: (double) height
        andFps: (double) fps
{
  if ( ( self = [super init] ) ) {
    _bus    = bus;
    _width  = width;
    _height = height;
    _fps    = fps;
  }
  return self;
}

//------------------------------------------------------------------------------

- (void) flip
{
  [[_view openGLContext] flushBuffer];
  // [_window repaint];  
}

//------------------------------------------------------------------------------

+ (NSString*) getApplicationName
{
  const NSDictionary *dict;
  NSString *appName = 0;

  dict = (const NSDictionary *)CFBundleGetInfoDictionary(CFBundleGetMainBundle());
  if (dict)
    appName = [dict objectForKey: @"CFBundleName"];
  
  if (![appName length])
    appName = [[NSProcessInfo processInfo] processName];

  return appName;
}

//------------------------------------------------------------------------------

- (void) setupMenu
{
  NSMenu *mainMenu;
  NSMenu *appleMenu;
  NSMenuItem *menuItem;
  NSString *appName = [ApplicationDelegate getApplicationName];
  
  mainMenu  = [[[NSMenu alloc] initWithTitle: @"MainMenu"] autorelease];
	menuItem  = [mainMenu 
	  addItemWithTitle: @"Apple" 
	  action: NULL 
	  keyEquivalent: @""
	];
  appleMenu = [[[NSMenu alloc] initWithTitle: @"Apple"] autorelease];
	[NSApp setAppleMenu: appleMenu];
	
  [appleMenu 
    addItemWithTitle: [@"About " stringByAppendingString: appName] 
    action: @selector (orderFrontStandardAboutPanel:) 
    keyEquivalent: @""
  ];

  [appleMenu addItem: [NSMenuItem separatorItem]];

  [appleMenu 
    addItemWithTitle: [@"Quit " stringByAppendingString:appName] 
    action: @selector (terminate:)
    keyEquivalent: @"q"
  ];	
  [mainMenu setSubmenu: appleMenu forItem: menuItem];
    
  [NSApp setMainMenu: mainMenu];
}

//------------------------------------------------------------------------------

- (void) run
{
  [NSApp setDelegate: self];

  Flatland::Logger::debug( "Starting main loop", "COCOA" );
  [NSApp run];
  Flatland::Logger::debug( "Terminating main loop", "COCOA" );
}

//------------------------------------------------------------------------------

- (void) applicationWillFinishLaunching: (NSNotification *) note
{ 
  [self setupMenu];

   unsigned int windowMask =   NSTitledWindowMask 
                             | NSClosableWindowMask 
                             | NSMiniaturizableWindowMask;
 
   NSRect rect = NSMakeRect ( 0, 0, _width, _height );
   _window = [NSWindow alloc];
   _window = [_window initWithContentRect: rect
                      styleMask: windowMask
                      backing: NSBackingStoreBuffered
                      defer: NO];

  _view = [[GLView alloc] initWithFrame: NSMakeRect( 0, 0, _width, _height)];
  [_window makeKeyAndOrderFront: _view];
  [_window makeFirstResponder: _view];
  [_window setContentView: _view];
}

//------------------------------------------------------------------------------

- (void) applicationDidFinishLaunching: (NSNotification *) note
{ 
  _updateTimer = [
    NSTimer 
    scheduledTimerWithTimeInterval: ( 1.0 / _fps ) 
    target: self 
    selector: @selector( onUpdate: ) 
    userInfo: nil
    repeats: YES
  ];
    
  Flatland::Logger::info( "Application finished launching", "COCOA" );
}

//------------------------------------------------------------------------------

- (void) onUpdate: (id) sender
{
  _bus->send( Flatland::UpdateEvent() );
}

//------------------------------------------------------------------------------

@end

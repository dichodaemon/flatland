// #include <Foundation/Foundation.h>
// #include <AppKit/AppKit.h>
// 
// @interface MyDelegate : NSObject
// {
//   NSWindow *myWindow;
// }
// - (void) printHello: (id)sender;
// - (void) createMenu;
// - (void) createWindow;
// - (void) applicationWillFinishLaunching: (NSNotification *)not;
// - (void) applicationDidFinishLaunching: (NSNotification *)not;
// @end
// 
// @implementation MyDelegate : NSObject 
// - (void) dealloc
// {
//   [super dealloc];
//   [myWindow autorelease];
// }
// 
// - (void) printHello: (id)sender
// {
//   printf ("Hello!\n");
// }
// 
// - (void) createMenu
// {
//   NSMenu *mainMenu = [NSApp mainMenu];
// 
//   // mainMenu = [[NSMenu alloc] initWithTitle: @"ffdfa"];
// 
//   [mainMenu addItemWithTitle: @"Quit"  
//             action: @selector (terminate:)  
//             keyEquivalent: @"q"];
//   [mainMenu setMenuBarVisible: YES];
//   // [NSApp setMainMenu: mainMenu];
//   // [mainMenu release];
// }
// 
// - (void) createWindow
// {
//   NSRect rect;
//   unsigned int styleMask =   NSTitledWindowMask 
//                            | NSMiniaturizableWindowMask;
//   NSButton *myButton;
//   NSSize buttonSize;
// 
//   myButton = [[NSButton new] autorelease];
//   [myButton setTitle: @"Print Hello!"];
//   [myButton sizeToFit];
//   [myButton setTarget: self];
//   [myButton setAction: @selector (printHello:)];
// 
//   buttonSize = [myButton frame].size;
//   rect = NSMakeRect (100, 100, 
//                      buttonSize.width * 10, 
//                      buttonSize.height);
// 
//   myWindow = [NSWindow alloc];
//   myWindow = [myWindow initWithContentRect: rect
//                        styleMask: styleMask
//                        backing: NSBackingStoreBuffered
//                        defer: NO];
//   [myWindow setTitle: @"This is a test window"];
//   [myWindow setContentView: myButton];
// }
// 
// - (void) applicationWillFinishLaunching: (NSNotification *)not
// {
//   [self createWindow];
//   [self createMenu];
// }
// 
// - (void) applicationDidFinishLaunching: (NSNotification *)not;
// {
//   [myWindow makeKeyAndOrderFront: nil];
// }
// @end

#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>

@interface NSApplication( MissingMethods )
- (void) setAppleMenu:( NSMenu * ) menu;
@end

@interface MyDelegate : NSObject
- (void) applicationWillFinishLaunching: (NSNotification *)not;
@end

@implementation MyDelegate : NSObject 
- (void) applicationWillFinishLaunching: (NSNotification *)not
{
  NSMenu *mainMenu;
  NSMenu *appleMenu;
  NSMenuItem *menuItem;

  mainMenu  = [[[NSMenu alloc] initWithTitle: @"MainMenu"] autorelease];
	menuItem  = [mainMenu addItemWithTitle: @"Apple" action: NULL keyEquivalent: @""];
	appleMenu = [[NSMenu alloc] initWithTitle: @"Apple"];
	[NSApp setAppleMenu: appleMenu];
	
  [appleMenu addItemWithTitle: @"About Application..." 
  action: @selector (orderFrontStandardAboutPanel:) 
  keyEquivalent: @""];

  [appleMenu addItem: [NSMenuItem separatorItem]];

  [appleMenu addItemWithTitle: @"Quit" 
    action: @selector (terminate:)
    keyEquivalent: @"q"];	
  [mainMenu setSubmenu: appleMenu forItem: menuItem];
    
  [NSApp setMainMenu: mainMenu];
  [[mainMenu itemAtIndex: 0] setTitle: @"Application"];

}
@end


int main (int argc, const char **argv)
{ 
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
  [NSApplication sharedApplication];
  [NSApp setDelegate: [MyDelegate new]];
  [NSApp run];
  
  [pool release];
  return 0;
  // return NSApplicationMain (argc, argv);
}

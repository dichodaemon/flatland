#ifndef COCOA_OBJECT_H
#define COCOA_OBJECT_H


#include <cstdlib>
#import <Cocoa/Cocoa.h>

class CocoaObject
{
public:
  CocoaObject();
  virtual ~CocoaObject();
private:
  static size_t _references;
  static NSAutoreleasePool * _pool;
};


#endif //COCOA_OBJECT_H

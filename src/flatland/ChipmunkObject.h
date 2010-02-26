#ifndef FLATLAND_CHIPMUNK_OBJECT_H
#define FLATLAND_CHIPMUNK_OBJECT_H


#include <chipmunk/chipmunk.h>
#include <cstdlib>

namespace Flatland
{


class ChipmunkObject
{
public:
  ChipmunkObject();
  virtual ~ChipmunkObject();
private:
  static size_t _references;
};


}


#endif //FLATLAND_CHIPMUNK_OBJECT_H

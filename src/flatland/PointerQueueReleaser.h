#ifndef FLATLAND_POINTER_QUEUE_RELEASER_H
#define FLATLAND_POINTER_QUEUE_RELEASER_H


namespace Flatland
{


template <typename T>
class PointerQueueReleaser
{
public:
  static void release( T value );
};

#include "PointerQueueReleaser.tpp"

}

#endif //FLATLAND_POINTER_QUEUE_RELEASER_H

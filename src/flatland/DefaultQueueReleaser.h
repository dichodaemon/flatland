#ifndef FLATLAND_DEFAULT_QUEUE_RELEASER_H
#define FLATLAND_DEFAULT_QUEUE_RELEASER_H


namespace Flatland
{


template <typename T>
class DefaultQueueReleaser
{
public:
  static void release( T value );
};

#include "DefaultQueueReleaser.tpp"

}

#endif //FLATLAND_DEFAULT_QUEUE_RELEASER_H

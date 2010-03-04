#ifndef FLATLAND_QUEUE_POLICY_H
#define FLATLAND_QUEUE_POLICY_H


namespace Flatland 
{


  enum QueuePolicy {
    WAIT_WHEN_FULL = 0,
    DISCARD_NEWEST = 1,
    DISCARD_OLDEST = 2
  };


}


#endif //FLATLAND_QUEUE_POLICY_H

#ifndef FLATLAND_CLOCK_H
#define FLATLAND_CLOCK_H


namespace Flatland
{


class Clock
{
public:
  Clock( double frequency );
  double tick();
  void pause( bool value );
  bool pause();
  double seconds();
  static void sleep( double seconds );
  static double systemSeconds();
private:
  double _period;
  double _firstTimestamp;
  bool   _pause;
  double _lastTimestamp;
};


}


#endif //FLATLAND_CLOCK_H

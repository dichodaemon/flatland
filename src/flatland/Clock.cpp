#include "Clock.h"
#include <sys/time.h>
#include <cmath>
#include <cstdio>

//------------------------------------------------------------------------------

Flatland::Clock::Clock( double frequency )
  : _period( 1.0 / frequency ),
    _firstTimestamp( 0 ),
    _pause( false )
{
}

//------------------------------------------------------------------------------

double
Flatland::Clock::tick()
{
  if ( _firstTimestamp == 0 && ! _pause ) {
    _firstTimestamp = seconds();
    _lastTimestamp  = seconds();
  }
  if ( _pause ) {
    return 0;
  }

  double current   = seconds();
  double sleepTime = _period - ( current - _lastTimestamp );
  if ( sleepTime > 0 ) {
    sleep( sleepTime );
  }
  current          = seconds();
  double elapsed   = current - _lastTimestamp;
  _lastTimestamp   = current;
  return elapsed;
}

//------------------------------------------------------------------------------

void
Flatland::Clock::pause( bool value )
{
  if ( _pause && ! value ) {
    _firstTimestamp = 0;
  }
  _pause = value;
}

//------------------------------------------------------------------------------

bool
Flatland::Clock::pause()
{
  return _pause;
}

//------------------------------------------------------------------------------

double
Flatland::Clock::seconds()
{
  return systemSeconds() - _firstTimestamp;
}

//------------------------------------------------------------------------------

void
Flatland::Clock::sleep( double seconds )
{
  if ( seconds == 0.0 ) {
    return;
  }

  struct timeval tv;
  tv.tv_sec  = floor( seconds );
  tv.tv_usec = ( seconds - tv.tv_sec ) * 1E6;
  select( 0, 0, 0, 0, &tv);
}

//------------------------------------------------------------------------------

double
Flatland::Clock::systemSeconds()
{
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return 1.0 * tv.tv_sec + tv.tv_usec * ( 1.0 * 1E-6 );
}


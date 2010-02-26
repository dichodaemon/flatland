#include "Color.h"

using namespace std;

//------------------------------------------------------------------------------

Flatland::Color::Color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha )
  : _red( red ),
    _green( green ),
    _blue( blue ),
    _alpha( alpha )
{
}

//------------------------------------------------------------------------------

uint8_t
Flatland::Color::red() const
{
  return _red;
}

//------------------------------------------------------------------------------

void
Flatland::Color::red( uint8_t value )
{
  _red = value;
}

//------------------------------------------------------------------------------

uint8_t
Flatland::Color::green() const
{
  return _green;
}

//------------------------------------------------------------------------------

void
Flatland::Color::green( uint8_t value )
{
  _green = value;
}

//------------------------------------------------------------------------------

uint8_t
Flatland::Color::blue() const
{
  return _blue;
}

//------------------------------------------------------------------------------

void
Flatland::Color::blue( uint8_t value )
{
  _blue = value;
}

//------------------------------------------------------------------------------

uint8_t
Flatland::Color::alpha() const
{
  return _alpha;
}

//------------------------------------------------------------------------------

void
Flatland::Color::alpha( uint8_t value )
{
  _alpha = value;
}

//------------------------------------------------------------------------------

Flatland::Color::operator uint32_t() const
{
  uint32_t result =   (uint32_t) _red   * 0x1000000
                    + (uint32_t) _green * 0x10000
                    + (uint32_t) _blue  * 0x100
                    + (uint32_t) _alpha;
  return result;
}

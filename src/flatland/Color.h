#ifndef FLATLAND_COLOR_H
#define FLATLAND_COLOR_H


#include <stdint.h>


namespace Flatland
{


class Color
{
public:
  Color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255 );
  uint8_t red() const;
  void red( uint8_t value );
  uint8_t green() const;
  void green( uint8_t value );
  uint8_t blue() const;
  void blue( uint8_t value );
  uint8_t alpha() const;
  void alpha( uint8_t value );
  operator uint32_t() const;

private:
  uint8_t _red;
  uint8_t _green;
  uint8_t _blue;
  uint8_t _alpha;
};


}

#endif //FLATLAND_COLOR_H

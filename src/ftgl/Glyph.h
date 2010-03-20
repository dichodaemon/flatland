#ifndef FLATLAND_GLYPH_H
#define FLATLAND_GLYPH_H


#include <flatland/BoundingBox.h>


namespace Flatland
{


class Glyph
{
public:
  Glyph();
  virtual ~Glyph();

  const BoundingBox & bounds() const;
  BoundingBox & bounds();
  const BoundingBox & textureCoordinates() const;
  BoundingBox & textureCoordinates();
  int skip() const;
  void skip( int value );
private:
  BoundingBox _bb;
  BoundingBox _textureCoordinates;
  int         _skip;
};


}

#endif //FLATLAND_GLYPH_H

#ifndef FLATLAND_FONT_H
#define FLATLAND_FONT_H


#include "FreeTypeObject.h"
#include "Glyph.h"
#include <flatland/Image.h>
#include <flatland/UnicodeText.h>
#include <map>
#include <string>


namespace Flatland
{


class Font
{
public:
  Font( 
    const std::string & filename, 
    size_t size, 
    const UnicodeText & charset = DEFAULT_CHAR_SET 
  );
  
  int  size() const;

private:
  typedef std::map< size_t, Glyph > GlyphTable;
  
  void renderToTexture(
    const FT_Face & fontFace,
    const UnicodeText::String32 & charset
  );
  
  static uint32_t DEFAULT_CHAR_SET[];  
  
  FreeTypeObject _freetype;
  Image          _image;
  size_t         _size;
  GlyphTable     _glyphs;
};


}


#endif //FLATLAND_FONT_H

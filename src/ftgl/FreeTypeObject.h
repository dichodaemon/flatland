#ifndef FREE_TYPE_OBJECT_H
#define FREE_TYPE_OBJECT_H


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <cstdlib>


class FreeTypeObject
{
public:
  FreeTypeObject();
  virtual ~FreeTypeObject();
  
  FT_Library & library();

private:
  static size_t     _references;
  static FT_Library _library;
};


#endif //FREE_TYPE_OBJECT_H

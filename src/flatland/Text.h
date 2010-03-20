#ifndef FLATLAND_TEXT_H
#define FLATLAND_TEXT_H


// #include <ftgl/config.h>
// #include <ftgl/FTGL/ftgles.h>
// #include <ftgl/FTGL/ftglesGlue.h>
#include <string>


namespace Flatland
{


class Text
{
public:
  Text();
  void operator()( const std::string & text );
  void draw();
  virtual ~Text();

private:
  // FTTextureFont * _font;
  // FTSimpleLayout  _layout;
  std::string     _text;
};
  
  
}


#endif //FLATLAND_TEXT_H

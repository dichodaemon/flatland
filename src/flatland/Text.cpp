#include "Text.h"
#include "Exceptions.h"

using namespace Flatland;

//------------------------------------------------------------------------------

Text::Text()
{
  // _font = new FTTextureFont( "/Library/Fonts/Arial.ttf" );
  // if ( _font->Error() ) {
  //   throw FontLoadingError( "/Library/Fonts/Arial.ttf" );
  // }
  // _font->FaceSize( 32 );
  // _font->CharMap( ft_encoding_unicode );
  // 
  // _layout.SetLineLength( 320.0 ); 
  // _layout.SetLineSpacing( 0.75 ); 
  // _layout.SetFont( _font );
  // _layout.SetAlignment( FTGL::ALIGN_CENTER );
}

//------------------------------------------------------------------------------

Text::~Text()
{
  // delete _font;
}

//------------------------------------------------------------------------------

void 
Text::draw()
{
  // ftglInitImmediateModeGL();
  // ftglColor4f( 255, 255, 255, 255 );
  // _layout.Render( 
  //   _text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK 
  // );
}
//------------------------------------------------------------------------------

void 
Text::operator()( const std::string & text )
{
  // _text = text;
}

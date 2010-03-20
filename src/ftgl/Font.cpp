#include "Font.h"
#include <flatland/BoundingBox.h>
#include <flatland/Exceptions.h>
#include <flatland/Logger.h>

#if defined (__APPLE__)
  #import <OpenGL/OpenGL.h>
#elif defined ( __linux )
  #include <GL/gl.h>
#endif

#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace Flatland;


//------------------------------------------------------------------------------

// ISO-8859-1
uint32_t Font::DEFAULT_CHAR_SET[] = {
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0x2A, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,
  0x00
};

//------------------------------------------------------------------------------

struct CompareGlyphs
{
    bool operator ()( FT_BitmapGlyph g1, FT_BitmapGlyph g2 ) const
    {
        return g1->bitmap.rows < g2->bitmap.rows;
    }
};

//------------------------------------------------------------------------------

Font::Font( const std::string & filename, size_t size, const UnicodeText & charset  )
  : _size( size )
{
  FT_Face fontFace;
  FT_Error error = FT_New_Face( _freetype.library(), filename.c_str(), 0, &fontFace );

  if ( error ) {
    Logger::error( "Problem loading font", "FreeType" );
    throw FileLoadError( "Problem loading font" );
  }

  renderToTexture( fontFace, charset );

  FT_Done_Face( fontFace );
}

//------------------------------------------------------------------------------

void 
Font::renderToTexture(
  const FT_Face & fontFace,
  const UnicodeText::String32 & charset
)
{
  GLint maxTextureSize;
  glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
  size_t charsPerRow = sqrt( charset.length() ) * 0.75;

  if ( charsPerRow * _size >=  static_cast< size_t >( maxTextureSize ) ) {
    _size = _size / charsPerRow;
  }

  size_t left   = 0;
  size_t top    = 0;
  size_t width  = 0;
  size_t height = _size * charsPerRow;

  width = 1;

  while ( width < _size * charsPerRow ) {
    width *= 2;
  }

  std::vector<size_t> tops( width, 0 );
  std::vector< uint8_t > buffer( width * height * 4 );

  FT_Error error = FT_Set_Pixel_Sizes( fontFace, _size, _size );

  if ( error ) {
    Logger::error( "Problem setting pixel size", "FreeType" );
  }

  error = FT_Select_Charmap( fontFace, FT_ENCODING_UNICODE );

  if ( error ) {
    Logger::error( "Problem assigning character map", "FreeType" );
  }

  typedef std::multimap< FT_BitmapGlyph, uint32_t, CompareGlyphs > GlyphTable;
  GlyphTable glyphs;

  for ( size_t i = 0; i < charset.length(); ++i ) {
    error = FT_Load_Char( fontFace, charset[i], FT_LOAD_TARGET_NORMAL );

    if ( error ) {
      Logger::error( "Problem loading char", "FreeType" );
    }

    FT_Glyph glyph;
    error = FT_Get_Glyph( fontFace->glyph, &glyph );

    if ( error ) {
      Logger::error( "Problem getting glyph", "FreeType" );
    }

    FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    FT_BitmapGlyph bitmapGlyph = ( FT_BitmapGlyph ) glyph;

    glyphs.insert( std::make_pair( bitmapGlyph, charset[i] ) );
  }


  unsigned int maxHeight = 0;
  std::map<uint32_t, BoundingBox> coords;

  for ( GlyphTable::const_iterator i = glyphs.begin(); i != glyphs.end(); ++i ) {
    // Get the bitmap of the current glyph
    Glyph     &    curGlyph    = _glyphs[i->second];
    FT_BitmapGlyph bitmapGlyph = i->first;
    FT_Bitmap   &  bitmap      = bitmapGlyph->bitmap;

    // Make sure we don't go over the texture width
    if ( left + bitmap.width + 1 >= width ) {
      left = 0;
    }

    // Compute the top coordinate
    top = tops[left];

    for ( int x = 0; x < bitmap.width + 1; ++x ) {
      top = std::max( top, tops[left + x] );
    }

    top++;

    // Make sure we don't go over the texture height -- resize it if we need more space
    if ( top + bitmap.rows + 1 >= height ) {
      height *= 2;
      buffer.resize( width * height * 4 );
    }

    // Store the character's position and size
    curGlyph.bounds().left( bitmapGlyph->left );
    curGlyph.bounds().top( -bitmapGlyph->top );
    curGlyph.bounds().right( curGlyph.bounds().left() + bitmap.width );
    curGlyph.bounds().bottom( bitmap.rows - bitmapGlyph->top );
    curGlyph.skip( bitmapGlyph->root.advance.x >> 16 );

    // Texture size may change, so let the texture coordinates be calculated later
    coords[i->second] = BoundingBox( 
      left + 1, top + 1, left + bitmap.width + 1, top + bitmap.rows + 1 
    );

    // Draw the glyph into our bitmap font
    const uint8_t * pixels = bitmap.buffer;

    for ( int y = 0; y < bitmap.rows; ++y ) {
      for ( int x = 0; x < bitmap.width; ++x ) {
        std::size_t index = x + left + 1 + ( y + top + 1 ) * width;
        buffer[index * 4 + 0] = 255;
        buffer[index * 4 + 1] = 255;
        buffer[index * 4 + 2] = 255;
        buffer[index * 4 + 3] = pixels[x];
      }

      pixels += bitmap.pitch;
    }

    // Update the rendering coordinates
    for ( int x = 0; x < bitmap.width + 1; ++x ) {
      tops[left + x] = top + bitmap.rows;
    }

    left += bitmap.width + 1;

    if ( top + bitmap.rows > maxHeight ) {
      maxHeight = top + bitmap.rows;
    }

    // Delete the glyph
    FT_Done_Glyph( ( FT_Glyph ) bitmapGlyph );
  }

// Create the font's texture
  height = maxHeight + 1;
  buffer.resize( width * height * 4 );
  
  _image.fromBuffer( &buffer[0], width * height * 4 );

// Now that the texture is created, we can precompute texture coordinates
  for ( std::size_t i = 0; i < charset.size(); ++i ) {
    uint32_t curChar = charset[i];
    BoundingBox & curCoord = coords[curChar];
    _glyphs[curChar].textureCoordinates() = BoundingBox(
      curCoord.left()   / width, 
      curCoord.top()    / height, 
      curCoord.right()  / width, 
      curCoord.bottom() / height
    );
  }
}
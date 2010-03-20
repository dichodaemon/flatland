#include "UnicodeText.h"
#include <stdexcept>
#include <string>

using namespace Flatland;

//------------------------------------------------------------------------------

namespace
{
template <typename T>
std::size_t stringLength( const T * s )
{
  std::size_t length = 0;

  while ( *s++ ) {
    length++;
  }

  return length;
}

std::locale getCurrentLocale()
{
  try {
    return std::locale( "" );
  } catch ( std::runtime_error & ) {
    // It seems some implementations don't know the "" locale
    // ( Mac OS, MinGW )

    return std::locale();
  }
}

}

//------------------------------------------------------------------------------

const int Flatland::UnicodeText::UTF8TrailingBytes[256] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

const uint32_t Flatland::UnicodeText::UTF8Offsets[6] = {
  0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
};

const uint8_t Flatland::UnicodeText::UTF8FirstBytes[7] = {
  0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
};

//------------------------------------------------------------------------------

UnicodeText::UnicodeText()
{
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const char * s )
{
  if ( s ) {
    std::size_t length = stringLength( s );

    if ( length > 0 ) {
      _string.reserve( length + 1 );
      UnicodeText::ANSIToUTF32( s, s + length, std::back_inserter( _string ) );
    }
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const wchar_t * s )
{
  if ( s ) {
    std::size_t length = stringLength( s );

    if ( length > 0 ) {
      // See comments below, in UnicodeText::UnicodeText( const std::wstring& )
      _string.reserve( length + 1 );

      switch ( sizeof( wchar_t ) ) {
      case 2 :
        UnicodeText::UTF16ToUTF32( s, s + length, std::back_inserter( _string ), 0 );
        break;
      case 4 :
        std::copy( s, s + length, std::back_inserter( _string ) );
        break;
      default :
        break;
      }
    }
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const uint8_t * s )
{
  if ( s ) {
    std::size_t length = stringLength( s );

    if ( length > 0 ) {
      _string.reserve( length + 1 );
      UnicodeText::UTF8ToUTF32( s, s + length, std::back_inserter( _string ), 0 );
    }
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const uint16_t * s )
{
  if ( s ) {
    std::size_t length = stringLength( s );

    if ( length > 0 ) {
      _string.reserve( length + 1 );
      UnicodeText::UTF16ToUTF32( s, s + length, std::back_inserter( _string ), 0 );
    }
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const uint32_t * s )
{
  if ( s ) {
    _string = s;
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const std::string & s )
{
  _string.reserve( s.length() + 1 );
  UnicodeText::ANSIToUTF32( s.begin(), s.end(), std::back_inserter( _string ) );
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const std::wstring & s )
{
  // This function assumes that 2-byte large wchar_t are encoded in UTF-16 ( Windows ), and
  // 4-byte large wchar_t are encoded using UTF-32 ( Unix )
  // Is that always true ? ( some platforms may use JIS Japanese encoding )
  // The macro __STDC_ISO_10646__ should help identifying UTF-32 compliant implementations

  _string.reserve( s.length() + 1 );

  // Select the proper function according to the ( supposed ) wchar_t system encoding
  switch ( sizeof( wchar_t ) ) {
    // wchar_t uses UTF-16 -- need a conversion
  case 2 :
    UnicodeText::UTF16ToUTF32( s.begin(), s.end(), std::back_inserter( _string ), 0 );
    break;
    // wchar_t uses UTF-32 -- direct copy
  case 4 :
    std::copy( s.begin(), s.end(), std::back_inserter( _string ) );
    break;

    // This should never happen
  default :
    break;
  }
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const UnicodeText::String8 & s )
{
  _string.reserve( s.length() + 1 );
  UnicodeText::UTF8ToUTF32( s.begin(), s.end(), std::back_inserter( _string ), 0 );
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const UnicodeText::String16 & s )
{
  _string.reserve( s.length() + 1 );
  UnicodeText::UTF16ToUTF32( s.begin(), s.end(), std::back_inserter( _string ), 0 );
}

//------------------------------------------------------------------------------

UnicodeText::UnicodeText( const UnicodeText::String32 & s )
{
  _string = s;
}

//------------------------------------------------------------------------------

UnicodeText::operator std::string() const
{
  std::string output;
  output.reserve( _string.length() + 1 );
  UnicodeText::UTF32ToANSI( _string.begin(), _string.end(), std::back_inserter( output ), 0, UnicodeText::getDefaultLocale() );
  return output;
}

//------------------------------------------------------------------------------

UnicodeText::operator std::wstring() const
{
  std::wstring output;
  output.reserve( _string.length() + 1 );

  // Select the proper function according to the ( supposed ) wchar_t system encoding
  switch ( sizeof( wchar_t ) ) {
    // wchar_t uses UTF-16 -- need a conversion
  case 2 : {
      UTF32ToUTF16( _string.begin(), _string.end(), std::back_inserter( output ), 0 );
      break;
    }

    // wchar_t uses UTF-32 -- direct copy
  case 4 : {
      std::copy( _string.begin(), _string.end(), std::back_inserter( output ) );
      break;
    }

    // This should never happen
  default :
    break;
  }

  return output;
}

//------------------------------------------------------------------------------

UnicodeText::operator UnicodeText::String8() const
{
  UnicodeText::String8 output;
  output.reserve( _string.length() * 4 + 1 );
  UnicodeText::UTF32ToUTF8( _string.begin(), _string.end(), std::back_inserter( output ), 0 );
  return output;
}

//------------------------------------------------------------------------------

UnicodeText::operator UnicodeText::String16() const
{
  UnicodeText::String16 output;
  output.reserve( _string.length() * 2 + 1 );
  UnicodeText::UTF32ToUTF16( _string.begin(), _string.end(), std::back_inserter( output ), 0 );
  return output;
}

//------------------------------------------------------------------------------

UnicodeText::operator const UnicodeText::String32 & () const
{
  return _string;
}

//------------------------------------------------------------------------------

const std::locale & UnicodeText::getDefaultLocale()
{
  static std::locale defaultLocale = getCurrentLocale();
  return defaultLocale;
}

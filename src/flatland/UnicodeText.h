#ifndef FLATLAND_UNICODE_TEXT_H
#define FLATLAND_UNICODE_TEXT_H


// Most of this code has been taken or adapted from Laurent Gomila's SFML.
// http://www.sfml-dev.org

#include <iterator>
#include <locale>
#include <string>
#include <cstdlib>


namespace Flatland
{


class UnicodeText
{
public:

  typedef std::basic_string<uint8_t>  String8;
  typedef std::basic_string<uint16_t> String16;
  typedef std::basic_string<uint32_t> String32;

  UnicodeText();
  UnicodeText( const char     *     s );
  UnicodeText( const wchar_t    *   s );
  UnicodeText( const uint8_t    *   s );
  UnicodeText( const uint16_t   *   s );
  UnicodeText( const uint32_t   *   s );
  UnicodeText( const std::string  & s );
  UnicodeText( const std::wstring & s );
  UnicodeText( const String8    &   s );
  UnicodeText( const String16   &   s );
  UnicodeText( const String32   &   s );

  operator       std::string() const;
  operator       std::wstring() const;
  operator       String8() const;
  operator       String16() const;
  operator const String32 &() const;

  template < typename IN, typename OUT >
  static OUT UTF32ToANSI(
    IN begin, IN end, OUT output,
    char replacement = '?', const std::locale & locale = getDefaultLocale()
  );

  template < typename IN, typename OUT >
  static OUT ANSIToUTF32(
    IN begin, IN end, OUT output,
    const std::locale & locale = getDefaultLocale()
  );

  template < typename IN, typename OUT >
  static OUT UTF8ToUTF16(
    IN begin, IN end, OUT output, uint16_t replacement = '?'
  );

  template < typename IN, typename OUT >
  static OUT UTF8ToUTF32(
    IN begin, IN end, OUT output, uint32_t replacement = '?'
  );

  template < typename IN, typename OUT >
  static OUT UTF16ToUTF8(
    IN begin, IN end, OUT output, uint8_t replacement = '?'
  );

  template < typename IN, typename OUT >
  static OUT UTF16ToUTF32(
    IN begin, IN end, OUT output, uint32_t replacement = '?'
  );

  template < typename IN, typename OUT >
  static OUT UTF32ToUTF8(
    IN begin, IN end, OUT output, uint8_t replacement = '?'
  );

  template < typename IN, typename OUT >
  static OUT UTF32ToUTF16(
    IN begin, IN end, OUT output, uint16_t replacement = '?'
  );

  template < typename T >
  static std::size_t GetUTF8Length( T Begin, T End );

  template < typename T >
  static std::size_t GetUTF16Length( T Begin, T End );

  template < typename T >
  static std::size_t GetUTF32Length( T Begin, T End );

private:
  static const std::locale & getDefaultLocale();
  static const int      UTF8TrailingBytes[256];
  static const uint32_t UTF8Offsets[6];
  static const uint8_t  UTF8FirstBytes[7];

  String32 _string;
};


#include "UnicodeText.tpp"


}


#endif //FLATLAND_UNICODE_TEXT_H

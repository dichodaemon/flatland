
//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF32ToANSI( IN begin, IN end, OUT output, char replacement, const std::locale & Locale )
{
#ifdef __MINGW32__

  // MinGW has a almost no support for UnicodeText stuff
  // As a consequence, the MinGW version of this function can only use the default locale
  // and ignores the one passed as parameter
  while ( begin < end ) {
    char char = 0;

    if ( wctomb( &Char, static_cast<wchar_t>( *begin++ ) ) >= 0 ) {
      *output++ = char;
    } else if ( replacement ) {
      *output++ = replacement;
    }
  }

#else

  // Get the facet of the locale which deals with character conversion
  const std::ctype<wchar_t>& Facet = std::use_facet< std::ctype<wchar_t> >( Locale );

  // Use the facet to convert each character of the input string
  while ( begin < end ) {
    *output++ = Facet.narrow( static_cast<wchar_t>( *begin++ ), replacement );
  }

#endif

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::ANSIToUTF32( IN begin, IN end, OUT output, const std::locale & Locale )
{
#ifdef __MINGW32__

  // MinGW has a almost no support for UnicodeText stuff
  // As a consequence, the MinGW version of this function can only use the default locale
  // and ignores the one passed as parameter
  while ( begin < end ) {
    wchar_t char = 0;
    mbtowc( &Char, &*begin, 1 );
    begin++;
    *output++ = static_cast<uint32_t>( char );
  }

#else

  // Get the facet of the locale which deals with character conversion
  const std::ctype<wchar_t>& Facet = std::use_facet< std::ctype<wchar_t> >( Locale );

  // Use the facet to convert each character of the input string
  while ( begin < end ) {
    *output++ = static_cast<uint32_t>( Facet.widen( *begin++ ) );
  }

#endif

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF8ToUTF16( IN begin, IN end, OUT output, uint16_t replacement )
{
  while ( begin < end ) {
    uint32_t c = 0;
    int TrailingBytes = UTF8TrailingBytes[static_cast<int>( *begin )];

    if ( begin + TrailingBytes < end ) {
      // First decode the UTF-8 character
      switch ( TrailingBytes ) {
      case 5 :
        c += *begin++;
        c <<= 6;
      case 4 :
        c += *begin++;
        c <<= 6;
      case 3 :
        c += *begin++;
        c <<= 6;
      case 2 :
        c += *begin++;
        c <<= 6;
      case 1 :
        c += *begin++;
        c <<= 6;
      case 0 :
        c += *begin++;
      }

      c -= UTF8Offsets[TrailingBytes];

      // Then encode it in UTF-16
      if ( c < 0xFFFF ) {
        // character can be converted directly to 16 bits, just need to check it's in the valid range
        if ( ( c >= 0xD800 ) && ( c <= 0xDFFF ) ) {
          // Invalid character (this range is reserved)
          if ( replacement ) {
            *output++ = replacement;
          }
        } else {
          // Valid character directly convertible to 16 bits
          *output++ = static_cast<uint16_t>( c );
        }
      } else if ( c > 0x0010FFFF ) {
        // Invalid character (greater than the maximum UnicodeText value)
        if ( replacement ) {
          *output++ = replacement;
        }
      } else {
        // character will be converted to 2 UTF-16 elements
        c -= 0x0010000;
        *output++ = static_cast<uint16_t>( ( c >> 10 )     + 0xD800 );
        *output++ = static_cast<uint16_t>( ( c & 0x3FFUL ) + 0xDC00 );
      }
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF8ToUTF32( IN begin, IN end, OUT output, uint32_t replacement )
{
  while ( begin < end ) {
    uint32_t c = 0;
    int TrailingBytes = UTF8TrailingBytes[static_cast<int>( *begin )];

    if ( begin + TrailingBytes < end ) {
      // First decode the UTF-8 character
      switch ( TrailingBytes ) {
      case 5 :
        c += *begin++;
        c <<= 6;
      case 4 :
        c += *begin++;
        c <<= 6;
      case 3 :
        c += *begin++;
        c <<= 6;
      case 2 :
        c += *begin++;
        c <<= 6;
      case 1 :
        c += *begin++;
        c <<= 6;
      case 0 :
        c += *begin++;
      }

      c -= UTF8Offsets[TrailingBytes];

      // Then write it if valid
      if ( ( c < 0xD800 ) || ( c > 0xDFFF ) ) {
        // Valid UTF-32 character
        *output++ = c;
      } else {
        // Invalid UTF-32 character
        if ( replacement ) {
          *output++ = replacement;
        }
      }
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF16ToUTF8( IN begin, IN end, OUT output, uint8_t replacement )
{
  while ( begin < end ) {
    uint32_t c = *begin++;

    // If it's a surrogate pair, first convert to a single UTF-32 character
    if ( ( c >= 0xD800 ) && ( c <= 0xDBFF ) ) {
      if ( begin < end ) {
        // The second element is valid : convert the two elements to a UTF-32 character
        uint32_t d = *begin++;

        if ( ( d >= 0xDC00 ) && ( d <= 0xDFFF ) ) {
          c = static_cast<uint32_t>( ( ( c - 0xD800 ) << 10 ) + ( d - 0xDC00 ) + 0x0010000 );
        }
      } else {
        // Invalid second element
        if ( replacement ) {
          *output++ = replacement;
        }
      }
    }

    // Then convert to UTF-8
    if ( c > 0x0010FFFF ) {
      // Invalid character (greater than the maximum UnicodeText value)
      if ( replacement ) {
        *output++ = replacement;
      }
    } else {
      // Valid character

      // Get number of bytes to write
      int bytesToWrite = 1;

      if      ( c <  0x80 ) {
        bytesToWrite = 1;
      } else if ( c <  0x800 ) {
        bytesToWrite = 2;
      } else if ( c <  0x10000 ) {
        bytesToWrite = 3;
      } else if ( c <= 0x0010FFFF ) {
        bytesToWrite = 4;
      }

      // Extract bytes to write
      uint8_t bytes[4];

      switch ( bytesToWrite ) {
      case 4 :
        bytes[3] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 3 :
        bytes[2] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 2 :
        bytes[1] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 1 :
        bytes[0] = static_cast<uint8_t> ( c | UTF8FirstBytes[bytesToWrite] );
      }

      // Add them to the output
      const uint8_t * currentByte = bytes;

      switch ( bytesToWrite ) {
      case 4 :
        *output++ = *currentByte++;
      case 3 :
        *output++ = *currentByte++;
      case 2 :
        *output++ = *currentByte++;
      case 1 :
        *output++ = *currentByte++;
      }
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF16ToUTF32( IN begin, IN end, OUT output, uint32_t replacement )
{
  while ( begin < end ) {
    uint16_t c = *begin++;

    if ( ( c >= 0xD800 ) && ( c <= 0xDBFF ) ) {
      // We have a surrogate pair, ie. a character composed of two elements
      if ( begin < end ) {
        uint16_t d = *begin++;

        if ( ( d >= 0xDC00 ) && ( d <= 0xDFFF ) ) {
          // The second element is valid : convert the two elements to a UTF-32 character
          *output++ = static_cast<uint32_t>( ( ( c - 0xD800 ) << 10 ) + ( d - 0xDC00 ) + 0x0010000 );
        } else {
          // Invalid second element
          if ( replacement ) {
            *output++ = replacement;
          }
        }
      }
    } else if ( ( c >= 0xDC00 ) && ( c <= 0xDFFF ) ) {
      // Invalid character
      if ( replacement ) {
        *output++ = replacement;
      }
    } else {
      // Valid character directly convertible to UTF-32
      *output++ = static_cast<uint32_t>( c );
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF32ToUTF8( IN begin, IN end, OUT output, uint8_t replacement )
{
  while ( begin < end ) {
    uint32_t c = *begin++;

    if ( c > 0x0010FFFF ) {
      // Invalid character (greater than the maximum UnicodeText value)
      if ( replacement ) {
        *output++ = replacement;
      }
    } else {
      // Valid character

      // Get number of bytes to write
      int bytesToWrite = 1;

      if      ( c <  0x80 ) {
        bytesToWrite = 1;
      } else if ( c <  0x800 ) {
        bytesToWrite = 2;
      } else if ( c <  0x10000 ) {
        bytesToWrite = 3;
      } else if ( c <= 0x0010FFFF ) {
        bytesToWrite = 4;
      }

      // Extract bytes to write
      uint8_t bytes[4];

      switch ( bytesToWrite ) {
      case 4 :
        bytes[3] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 3 :
        bytes[2] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 2 :
        bytes[1] = static_cast<uint8_t>( ( c | 0x80 ) & 0xBF );
        c >>= 6;
      case 1 :
        bytes[0] = static_cast<uint8_t> ( c | UTF8FirstBytes[bytesToWrite] );
      }

      // Add them to the output
      const uint8_t * currentByte = bytes;

      switch ( bytesToWrite ) {
      case 4 :
        *output++ = *currentByte++;
      case 3 :
        *output++ = *currentByte++;
      case 2 :
        *output++ = *currentByte++;
      case 1 :
        *output++ = *currentByte++;
      }
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN, typename OUT >
inline OUT UnicodeText::UTF32ToUTF16( IN begin, IN end, OUT output, uint16_t replacement )
{
  while ( begin < end ) {
    uint32_t c = *begin++;

    if ( c < 0xFFFF ) {
      // character can be converted directly to 16 bits, just need to check it's in the valid range
      if ( ( c >= 0xD800 ) && ( c <= 0xDFFF ) ) {
        // Invalid character (this range is reserved)
        if ( replacement ) {
          *output++ = replacement;
        }
      } else {
        // Valid character directly convertible to 16 bits
        *output++ = static_cast<uint16_t>( c );
      }
    } else if ( c > 0x0010FFFF ) {
      // Invalid character (greater than the maximum UnicodeText value)
      if ( replacement ) {
        *output++ = replacement;
      }
    } else {
      // character will be converted to 2 UTF-16 elements
      c -= 0x0010000;
      *output++ = static_cast<uint16_t>( ( c >> 10 )     + 0xD800 );
      *output++ = static_cast<uint16_t>( ( c & 0x3FFUL ) + 0xDC00 );
    }
  }

  return output;
}

//------------------------------------------------------------------------------

template < typename IN >
inline std::size_t UnicodeText::GetUTF8Length( IN begin, IN end )
{
  std::size_t length = 0;

  while ( begin < end ) {
    int byteCount = UTF8TrailingBytes[static_cast<int>( *begin )];

    if ( begin + byteCount < end ) {
      ++length;
    }

    begin += byteCount + 1;
  }

  return length;
}


template < typename IN >
inline std::size_t UnicodeText::GetUTF16Length( IN begin, IN end )
{
  std::size_t length = 0;

  while ( begin < end ) {
    if ( ( *begin >= 0xD800 ) && ( *begin <= 0xDBFF ) ) {
      ++begin;

      if ( ( begin < end ) && ( ( *begin >= 0xDC00 ) && ( *begin <= 0xDFFF ) ) ) {
        ++length;
      }
    } else {
      ++length;
    }

    ++begin;
  }

  return length;
}


template < typename IN >
inline std::size_t UnicodeText::GetUTF32Length( IN begin, IN end )
{
  return end - begin;
}

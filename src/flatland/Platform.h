#ifndef FLATLAND_PLATFORM_H
#define FLATLAND_PLATFORM_H


#if defined (__linux)
  #define LIBRARY_EXT ".so"
#elif defined (__APPLE__)
  #define LIBRARY_EXT ".dylib"
#elif defined (_WIN32)
  #define LIBRARY_EXT ".dll"
#endif


#endif //FLATLAND_PLATFORM_H
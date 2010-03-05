ADD_DEFINITIONS( -DPLUGIN_LIBRARIES )
ADD_DEFINITIONS( -DPTHREADS )


#-------------------------------------------------------------------------------
# Iniparser
#-------------------------------------------------------------------------------

file( GLOB INIPARSER_SRC iniparser/*.c )

add_library( iniparser SHARED ${INIPARSER_SRC} )

sm_cpp_install_binaries( iniparser )

#-------------------------------------------------------------------------------
# Ftgl
#-------------------------------------------------------------------------------
# 
# file(
#   GLOB FTGL_SRC
#   ftgl/*.cpp
#   ftgl/FTFont/*.cpp
#   ftgl/FTGL/*.cpp
#   ftgl/FTGlyph/*.cpp
#   ftgl/FTLayout/*.cpp
# )

# add_library( ftgl SHARED ${FTGL_SRC} )

# sm_cpp_install_binaries( ftgl )

#-------------------------------------------------------------------------------
# Chipmunk
#-------------------------------------------------------------------------------

file( GLOB CHIPMUNK_SRC chipmunk/*.c chipmunk/constraints/*.c )

add_library( chipmunk SHARED ${CHIPMUNK_SRC} )
set_target_properties(
  chipmunk
  PROPERTIES COMPILE_FLAGS "-std=gnu99 -ffast-math"
  DEFINE_SYMBOL NDEBUG
)

sm_cpp_install_binaries( chipmunk )


#-------------------------------------------------------------------------------
# Flatland
#-------------------------------------------------------------------------------

include( FindOpenAL )

if( OPENAL_FOUND )
  message( "OpenAL Found" )
  include_directories( OPENAL_INCLUDE_DIR )
else( OPENAL_FOUND )
  message( "OpenAL not found" )
endif( OPENAL_FOUND )

find_library( DL_LIB dl )

file( GLOB FLATLAND_SRC flatland/*.cpp )

add_library( flatland SHARED ${FLATLAND_SRC} )
target_link_libraries( flatland iniparser chipmunk ${DL_LIB} ${OPENAL_LIBRARY} )

sm_cpp_install( flatland )

#-------------------------------------------------------------------------------
# MacOS Backend
#-------------------------------------------------------------------------------

find_library( COCOA_LIB Cocoa )

file( GLOB FLATLAND_MACOS_SRC flatland_macos/*.mm )

add_library( flatland_macos SHARED ${FLATLAND_MACOS_SRC} )
target_link_libraries(
  flatland_macos
  iniparser
  chipmunk
  flatland
  ${COCOA_LIB}
)

sm_cpp_install( flatland_macos )

#-------------------------------------------------------------------------------
# OpenGL Backend
#-------------------------------------------------------------------------------

include( FindOpenGL )
include( FindSDL )


if( OPENGL_FOUND )
  message( "OpenGL Found" )
  include_directories( ${OPENGL_INCLUDE_DIR} )
else( OPENGL_FOUND )
  message( "OpenGL not found" )
endif( OPENGL_FOUND )  

if( SDL_FOUND )
  include_directories( SDL_INCLUDE_DIR )
else( SDL_FOUND )
  message( "SDL not found" )
endif( SDL_FOUND )

# find_library( ALUT_LIB alut )

file( GLOB FLATLAND_GL_SRC flatland_gl/*.cpp )

add_library( flatland_gl SHARED ${FLATLAND_GL_SRC} )
target_link_libraries(
  flatland_gl
  iniparser
  chipmunk
  flatland
  ${SDL_LIBRARY}
  ${OPENGL_gl_LIBRARY}
)

sm_cpp_install( flatland_gl )

#-------------------------------------------------------------------------------
# Sandbox
#-------------------------------------------------------------------------------


# add_executable( example1 sandbox/example1.cpp )
# target_link_libraries( example1 flatland )

# add_executable( whip sandbox/whip.cpp sandbox/GameObject.cpp sandbox/ChipmunkPainter.cpp)
# target_link_libraries( whip flatland )

if ( MACOSX )
  find_library( FOUNDATION_LIB Foundation )
  
  add_executable( 
    ropeman MACOSX_BUNDLE 
    sandbox/ropeman.cpp 
    sandbox/GameObject.cpp 
    sandbox/ChipmunkPainter.cpp
  )

  set( APPLE_GUI_IDENTIFIER net.dizanvasquez.Ropeman )
  set( APPLE_GUI_BUNDLE_NAME Ropeman )
  
  set_target_properties(
    ropeman PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/macos/AppleInfo.plist
    MACOSX_PACKAGE_LOCATION MacOSX 
  )

  target_link_libraries( ropeman flatland ${COCOA_LIB} )
  
else ( MACOSX )
  add_executable( ropeman sandbox/ropeman.cpp sandbox/GameObject.cpp sandbox/ChipmunkPainter.cpp)
  target_link_libraries( ropeman flatland )
endif ( MACOSX )

# add_executable( testsound sandbox/testsound.cpp )
# target_link_libraries( testsound ${OPENAL_LIBRARY} ${ALUT_LIB} )

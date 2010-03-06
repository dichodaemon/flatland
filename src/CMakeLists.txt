#-------------------------------------------------------------------------------
# Iniparser
#-------------------------------------------------------------------------------

file( GLOB INIPARSER_SRC iniparser/*.c )

add_library( iniparser ${INIPARSER_SRC} )

#-------------------------------------------------------------------------------
# Chipmunk
#-------------------------------------------------------------------------------

file( GLOB CHIPMUNK_SRC chipmunk/*.c chipmunk/constraints/*.c )

add_library( chipmunk ${CHIPMUNK_SRC} )
set_target_properties(
  chipmunk
  PROPERTIES COMPILE_FLAGS "-std=gnu99 -ffast-math"
  DEFINE_SYMBOL NDEBUG
)

#-------------------------------------------------------------------------------
# Flatland
#-------------------------------------------------------------------------------

# ADD_DEFINITIONS( -DPLUGIN_LIBRARIES )
ADD_DEFINITIONS( -DPTHREADS )
ADD_DEFINITIONS( -DPTHREADS )

include( FindOpenAL )
include( FindOpenGL )
include( FindSDL )


if( OPENGL_FOUND )
  message( "OpenGL Found" )
  include_directories( ${OPENGL_INCLUDE_DIR} )
else( OPENGL_FOUND )
  message( "OpenGL not found" )
endif( OPENGL_FOUND )  

if( OPENAL_FOUND )
  message( "OpenAL Found" )
  include_directories( OPENAL_INCLUDE_DIR )
else( OPENAL_FOUND )
  message( "OpenAL not found" )
endif( OPENAL_FOUND )

file( GLOB FLATLAND_SRC flatland/*.cpp )

if( MACOSX )
  file( GLOB FLATLAND_MACOS_SRC flatland_macos/*.mm )
  set( FLATLAND_SRC ${FLATLAND_SRC} ${FLATLAND_MACOS_SRC} )
endif( MACOSX )

file( GLOB FLATLAND_GL_SRC flatland_gl/*.cpp )
set( FLATLAND_SRC ${FLATLAND_SRC} ${FLATLAND_GL_SRC} )

add_library( flatland ${FLATLAND_SRC} )
target_link_libraries( 
  flatland 
  iniparser 
  chipmunk 
  ${OPENAL_LIBRARY} 
  ${OPENGL_gl_LIBRARY}
)


if ( MACOSX )
  find_library( COCOA_LIB Cocoa )
  find_library( AUDIO_TOOLBOX_LIB AudioToolbox )
  target_link_libraries( flatland ${AUDIO_TOOLBOX_LIB} ${COCOA_LIB} )
endif ( MACOSX )


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
    sandbox/SoundManager.cpp
  )

  set( APPLE_GUI_IDENTIFIER net.dizanvasquez.Ropeman )
  set( APPLE_GUI_BUNDLE_NAME Ropeman )
  
  set_target_properties(
    ropeman PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/macos/AppleInfo.plist
    MACOSX_PACKAGE_LOCATION MacOSX 
  )

  target_link_libraries( 
    ropeman 
    flatland 
  )
  
else ( MACOSX )
  add_executable( ropeman sandbox/ropeman.cpp sandbox/GameObject.cpp sandbox/ChipmunkPainter.cpp)
  target_link_libraries( ropeman flatland )
endif ( MACOSX )

# add_executable( testsound sandbox/testsound.cpp )
# target_link_libraries( testsound ${OPENAL_LIBRARY} ${ALUT_LIB} )

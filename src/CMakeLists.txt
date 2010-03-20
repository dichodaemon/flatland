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
# Soil
#-------------------------------------------------------------------------------

file( GLOB SOIL_SRC soil/*.c  )

add_library( soil ${SOIL_SRC} )
set_target_properties(
  soil
  PROPERTIES COMPILE_FLAGS "-std=gnu99 -ffast-math"
)

#-------------------------------------------------------------------------------
# Freetype
#-------------------------------------------------------------------------------

file( GLOB FREETYPE_SRC 
  freetype/autofit/*.c  
  freetype/base/*.c  
  freetype/bdf/*.c  
  freetype/cache/*.c  
  freetype/cff/*.c  
  freetype/cid/*.c  
  # freetype/gxvalid/*.c  
  freetype/gzip/*.c  
  freetype/lzw/*.c  
  # freetype/otvalid/*.c  
  freetype/pcf/*.c  
  freetype/pfr/*.c  
  freetype/psaux/*.c  
  freetype/pshinter/*.c  
  freetype/psnames/*.c  
  freetype/raster/*.c  
  freetype/sfnt/*.c  
  freetype/smooth/*.c  
  # freetype/tools/*.c  
  freetype/truetype/*.c  
  freetype/type1/*.c  
  freetype/type42/*.c  
  freetype/winfonts/*.c  
)

add_library( freetype ${FREETYPE_SRC} )
set_target_properties(
  freetype
  PROPERTIES COMPILE_FLAGS "-std=gnu99 -ffast-math -DFT2_BUILD_LIBRARY -DAF_SCRIPT_LATIN2"
)

include_directories( freetype )

#-------------------------------------------------------------------------------
# FTGL
#-------------------------------------------------------------------------------

file( GLOB FTGL_SRC 
  ftgl/*.cpp  
  # ftgl/FreeTypeObject.cpp
)

add_library( ftgl ${FTGL_SRC} )
set_target_properties(
  ftgl
  PROPERTIES COMPILE_FLAGS "-ffast-math"
)

include_directories( ftgl )

#-------------------------------------------------------------------------------
# Flatland
#-------------------------------------------------------------------------------

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
  soil
  freetype
  # ftgl
  ${OPENAL_LIBRARY} 
  ${OPENGL_gl_LIBRARY}
)


if ( MACOSX )
  find_library( COCOA_LIB Cocoa )
  find_library( AUDIO_TOOLBOX_LIB AudioToolbox )
  target_link_libraries( flatland ${AUDIO_TOOLBOX_LIB} ${COCOA_LIB} )
endif ( MACOSX )


#-------------------------------------------------------------------------------
# Ropeman
#-------------------------------------------------------------------------------

file( GLOB ROPEMAN_SRC ropeman/*.cpp ) 
sm_glob_recurse( ROPEMAN_RESOURCES ropeman/resources/* ) 

if ( MACOSX )
   
  add_executable( 
    ropeman MACOSX_BUNDLE 
    ${ROPEMAN_SRC}
    ${ROPEMAN_RESOURCES}
  )

  set( APPLE_GUI_IDENTIFIER net.dizanvasquez.Ropeman )
  set( APPLE_GUI_BUNDLE_NAME Ropeman )
  
  set_target_properties(
    ropeman PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/macos/AppleInfo.plist
    MACOSX_PACKAGE_LOCATION MacOSX 
  )

  set_source_files_properties(
    ${ROPEMAN_RESOURCES}
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
  )

else ( MACOSX )
  add_executable( 
    ropeman 
    ${ROPEMAN_SRC}
  )

endif ( MACOSX )

target_link_libraries( 
  ropeman 
  flatland 
)

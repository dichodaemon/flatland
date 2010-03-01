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

file( GLOB FLATLAND_SRC flatland/*.cpp )
file( GLOB FLATLAND_IMPL_SRC _flatland/*.cpp )

find_library( DL_LIB dl )

add_library( flatland SHARED ${FLATLAND_SRC} ${FLATLAND_IMPL_SRC} )
target_link_libraries( flatland iniparser chipmunk ${DL_LIB} )

sm_cpp_install( flatland )

#-------------------------------------------------------------------------------
# SDL Backend
#-------------------------------------------------------------------------------

# file( GLOB FLATLAND_SDL_SRC flatland_sdl/*.cpp )
# 
# find_library( SDL_LIB SDL )
# find_library( SDL_GFX_LIB SDL_gfx )
# 
# add_library( flatland_sdl SHARED ${FLATLAND_SDL_SRC} )
# target_link_libraries(
#   flatland_sdl
#   iniparser
#   chipmunk
#   flatland
#   ${SDL_LIB}
#   ${SDL_GFX_LIB}
# )
# 
# sm_cpp_install( flatland_sdl )
# 
#-------------------------------------------------------------------------------
# OpenGL Backend
#-------------------------------------------------------------------------------

include( FindSDL )
include( FindOpenGL )

if( SDL_FOUND )
  message( "SDL Found" )
  include_directories( SDL_INCLUDE_DIR )
else( SDL_FOUND )
  message( "SDL not found" )
endif( SDL_FOUND )  

if( OPENGL_FOUND )
  message( "OpenGL Found" )
  include_directories( OPENGL_INCLUDE_DIR )
else( OPENGL_FOUND )
  message( "OpenGL not found" )
endif( OPENGL_FOUND )  

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

add_executable( ropeman sandbox/ropeman.cpp sandbox/GameObject.cpp sandbox/ChipmunkPainter.cpp)
target_link_libraries( ropeman flatland )

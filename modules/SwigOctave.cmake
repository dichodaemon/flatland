find_program( SWIG_COMMAND NAMES swig PATHS "/usr/bin" )

if ( SWIG_COMMAND )
  set( SWIG_FOUND "YES" )
else ( SWIG_COMMAND )
  message( STATUS "swig command not found. No octave bindings will be available." )
endif( SWIG_COMMAND )


find_program( MAKEOCT_COMMAND NAMES mkoctfile PATHS "/usr/bin" )

if ( MAKEOCT_COMMAND )
  set( SWIG_FOUND "YES" )
else ( MAKEOCT_COMMAND )
  message( STATUS "mkoctfile command not found. No octave bindings will be available." )
endif( MAKEOCT_COMMAND )

#-------------------------------------------------------------------------------

macro ( SWIG_OCTAVE MODULE )
  set( MODULE_SOURCE ${PROJECT_BINARY_DIR}/src/${MODULE}_octave.cpp )
  set( ${MODULE}_INFO ${PROJECT_SOURCE_DIR}/src/${MODULE}.i )
  set( MODULE_M ${PROJECT_BINARY_DIR}/src/${MODULE}.m )
  set( LINKED_LIBRARIES ${ARGN} )
  set( SWIG_LINKER_FLAGS "-Xlinker -export-dynamic" )
  
  get_directory_property( MODULE_INCLUDE_DIRS INCLUDE_DIRECTORIES )
  set( SWIG_INCLUDE_STR )
  foreach( it ${MODULE_INCLUDE_DIRS})
    set(SWIG_INCLUDE_STR ${SWIG_INCLUDE_STR} "-I${it}")
  endforeach(it)  
  
  set( SWIG_LIB_STR )
  foreach( it ${LINKED_LIBRARIES})
    set(SWIG_LIB_STR ${SWIG_LIB_STR} "-l${it}")
  endforeach(it)  

  message( STATUS "Swig include string:${SWIG_INCLUDE_STR}" )
  
  add_custom_command( 
    OUTPUT ${MODULE_SOURCE} ${MODULE_M}
    DEPENDS ${${MODULE}_INFO}
    COMMAND ${SWIG_COMMAND}
      -octave
      -c++
      -o ${MODULE_SOURCE}
      ${SWIG_INCLUDE_STR}
      ${${MODULE}_INFO}
    COMMENT   "Generating octave module source for '${MODULE}' from '${${MODULE}_INFO}'"
  )
  
  set( MODULE_OCT ${MODULE}.oct )

  add_custom_target( 
    Name ALL
    DEPENDS ${MODULE_SOURCE}
    COMMAND ${MAKEOCT_COMMAND} ${MODULE_SOURCE} ${SWIG_LIB_STR}
    COMMENT   "Generating octave oct file for '${MODULE}' from '${MODULE_SOURCE}'"
  )
  
#   set_target_properties( ${MODULE_LIB} PROPERTIES PREFIX "" OUTPUT_NAME _${MODULE} )
#   set_target_properties( ${MODULE_LIB} PROPERTIES LINK_FLAGS ${SWIG_LINKER_FLAGS} )
#   message( STATUS "OCTAVE Linked libraries:" ${LINKED_LIBRARIES} )
#   target_link_libraries( ${MODULE_LIB} ${LINKED_LIBRARIES} )

#   install(
#     TARGETS ${MODULE_OCT}
#     LIBRARY DESTINATION lib/octave/3.0.1/oct/i486-pc-linux-gnu/ COMPONENT default
    #LIBRARY DESTINATION lib/python2.5/site-packages/ COMPONENT default
#   )  
#   install(
#     FILES ${MODULE_M}
#     DESTINATION share/octave/3.0.1/m/ COMPONENT default
#   )  
endmacro ( SWIG_OCTAVE MODULE )
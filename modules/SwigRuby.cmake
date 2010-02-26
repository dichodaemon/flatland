find_program( SWIG_COMMAND NAMES swig PATHS "/usr/bin" )

if ( SWIG_COMMAND )
  set( SWIG_FOUND "YES" )
else ( SWIG_COMMAND )
  message( STATUS "swig command not found. No ruby bindings will be available." )
endif( SWIG_COMMAND )

#-------------------------------------------------------------------------------

macro ( SWIG_RUBY MODULE )
  set( MODULE_SOURCE ${PROJECT_BINARY_DIR}/src/${MODULE}.cpp )
  set( ${MODULE}_INFO ${PROJECT_SOURCE_DIR}/src/${MODULE}.i )
  set( MODULE_RB ${PROJECT_BINARY_DIR}/src/${MODULE}.rb )
  set( LINKED_LIBRARIES ${ARGN} )
  set( SWIG_LINKER_FLAGS "-Xlinker -export-dynamic" )
  
  find_package( Ruby )
  include_directories(${RUBY_INCLUDE_PATH})
  get_directory_property( MODULE_INCLUDE_DIRS INCLUDE_DIRECTORIES )
  set( SWIG_INCLUDE_STR )
  foreach( it ${MODULE_INCLUDE_DIRS})
    set(SWIG_INCLUDE_STR ${SWIG_INCLUDE_STR} "-I${it}")
  endforeach(it)  
  
  message( STATUS "Swig include string:${SWIG_INCLUDE_STR}" )
  
  add_custom_command( 
    OUTPUT ${MODULE_SOURCE} ${MODULE_RB}
    DEPENDS ${${MODULE}_INFO}
    COMMAND ${SWIG_COMMAND}
      -ruby
      -c++
      -o ${MODULE_SOURCE}
      ${SWIG_INCLUDE_STR}
      ${${MODULE}_INFO}
    COMMENT   "Generating module source for '${MODULE}' from '${${MODULE}_INFO}'"
  )
  
  set( MODULE_LIB m_${MODULE} )
  add_library( 
    ${MODULE_LIB} SHARED 
    ${MODULE_SOURCE}
  )
  
  set_target_properties( ${MODULE_LIB} PROPERTIES PREFIX "" OUTPUT_NAME _${MODULE} )
  set_target_properties( ${MODULE_LIB} PROPERTIES LINK_FLAGS ${SWIG_LINKER_FLAGS} )
  target_link_libraries( ${MODULE_LIB} ${LINKED_LIBRARIES} )

  install(
    TARGETS ${MODULE_LIB}
    LIBRARY DESTINATION local/lib/site_ruby/1.8/i486-linux COMPONENT default
  )  
  install(
    FILES ${MODULE_RB}
    DESTINATION local/lib/site_ruby/1.8/i486-linux COMPONENT default
  )  
endmacro ( SWIG_RUBY MODULE )
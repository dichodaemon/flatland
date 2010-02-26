find_program( SWIG_COMMAND NAMES swig PATHS "/usr/bin" )

if ( SWIG_COMMAND )
  set( SWIG_FOUND "YES" )
else ( SWIG_COMMAND )
  message( STATUS "swig command not found. No python bindings will be available." )
endif( SWIG_COMMAND )


#-------------------------------------------------------------------------------

macro ( SWIG_PYTHON MODULE )
  set( MODULE_SOURCE ${PROJECT_BINARY_DIR}/src/${MODULE}_python.cpp )
  set( ${MODULE}_INFO ${PROJECT_SOURCE_DIR}/src/${MODULE}.i )
  set( MODULE_PY ${PROJECT_BINARY_DIR}/src/${MODULE}.py )
  set( LINKED_LIBRARIES ${ARGN} )
  set( SWIG_LINKER_FLAGS "-Xlinker -export-dynamic" )
  
  find_package(PythonLibs)
  include_directories(${PYTHON_INCLUDE_PATH})
  get_directory_property( MODULE_INCLUDE_DIRS INCLUDE_DIRECTORIES )
  set( SWIG_INCLUDE_STR )
  foreach( it ${MODULE_INCLUDE_DIRS})
    set(SWIG_INCLUDE_STR ${SWIG_INCLUDE_STR} "-I${it}")
  endforeach(it)  
  
  message( STATUS "Swig include string:${SWIG_INCLUDE_STR}" )
  
  add_custom_command( 
    OUTPUT ${MODULE_SOURCE} ${MODULE_PY}
    DEPENDS ${${MODULE}_INFO}
    COMMAND ${SWIG_COMMAND}
      -python
      -c++
      -threads
      -o ${MODULE_SOURCE}
      ${SWIG_INCLUDE_STR}
      ${${MODULE}_INFO}
    COMMENT   "Generating python module source for '${MODULE}' from '${${MODULE}_INFO}'"
  )
  
  set( MODULE_LIB m_${MODULE} )
  add_library( 
    ${MODULE_LIB} SHARED 
    ${MODULE_SOURCE}
  )
  
  set_target_properties( ${MODULE_LIB} PROPERTIES PREFIX "" OUTPUT_NAME _${MODULE} )
  set_target_properties( ${MODULE_LIB} PROPERTIES LINK_FLAGS ${SWIG_LINKER_FLAGS} )
  message( STATUS "PYTHON Linked libraries:" ${LINKED_LIBRARIES} )
  target_link_libraries( ${MODULE_LIB} ${LINKED_LIBRARIES} )

  find_path( 
    PYTHON_SITE_PACKAGES_PATH .
    PATHS /usr/lib
    PATH_SUFFIXES 
      python2.6/dist-packages
      python2.5/site-packages
      python2.4/site-packages
    NO_DEFAULT_PATH
  )  

  install(
    TARGETS ${MODULE_LIB}
    LIBRARY DESTINATION ${CMAKE_INSTALL_ROOT}/${PYTHON_SITE_PACKAGES_PATH} COMPONENT default
  )  
  install(
    FILES ${MODULE_PY}
    DESTINATION ${CMAKE_INSTALL_ROOT}/${PYTHON_SITE_PACKAGES_PATH} COMPONENT default
  )  
endmacro ( SWIG_PYTHON MODULE )
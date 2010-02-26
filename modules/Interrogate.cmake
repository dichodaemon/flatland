find_program( INTERROGATE_COMMAND NAMES interrogate PATHS "/usr/bin" )
find_program( INTERROGATE_MODULE_COMMAND NAMES interrogate_module PATHS "/usr/bin" )

if ( INTERROGATE_COMMAND )
  set( INTERROGATE_FOUND "YES" )
else ( INTERROGATE_COMMAND )
  message( STATUS "interrogate command not found. No python bindings will be available." )
endif( INTERROGATE_COMMAND )

#-------------------------------------------------------------------------------

macro ( INTERROGATE_LIBRARY MODULE LIBRARY SOURCE_DIR )
  sm_cpp_include_dir( PANDA panda3d )
  include( FindPythonLibs )
  include_directories( ${PYTHON_INCLUDE_PATH} )
 
  set( SOURCES ${ARGN} )
  foreach( SOURCE ${ARGN} )
    list( APPEND MODULE_DEPENDS "${SOURCE_DIR}/./${SOURCE}")
  endforeach( SOURCE )

  set( LIBRARY_INFO ${PROJECT_BINARY_DIR}/src/${MODULE}_${LIBRARY}.in )
  set( LIBRARY_SOURCE ${PROJECT_BINARY_DIR}/src/${MODULE}_${LIBRARY}.cpp )

  message( STATUS "INTERROGATE FLAGS: ${INTERROGATE_FLAGS}" )

  add_custom_command( 
    OUTPUT  ${LIBRARY_INFO} ${LIBRARY_SOURCE}
    DEPENDS ${MODULE_DEPENDS}
    COMMAND  ${INTERROGATE_COMMAND}
      -od ${LIBRARY_INFO} -oc ${LIBRARY_SOURCE}
      -library ${LIBRARY} -module lib${MODULE}
      -fnames -python-native -string -promiscuous -refcount
      -DCPPPARSER -D__STDC__=1 -D__cplusplus -D__i386__ -D__const=const -Dvolatile=
      -S/usr/include/panda3d ${INTERROGATE_FLAGS}
      -S/usr/include/panda3d/parser-inc
      -S${SOURCE_DIR}
      -S${SOURCE_DIR}/parser-inc
      -srcdir ${SOURCE_DIR}
      ${SOURCES}
    COMMENT   "Generating library '${LIBRARY}' from '${SOURCES}'"
  )
  list( APPEND ${MODULE}_SOURCES ${LIBRARY_SOURCE} )
  list( APPEND ${MODULE}_INFO ${LIBRARY_INFO} )
endmacro ( INTERROGATE_LIBRARY MODULE LIBRARY SOURCE_DIR )

#-------------------------------------------------------------------------------

macro ( INTERROGATE_MODULE MODULE )
  find_path( 
    PYTHON_SITE_PACKAGES_PATH .
    PATHS /usr/lib
    PATH_SUFFIXES 
      python2.6/dist-packages
      python2.5/site-packages
      python2.4/site-packages
    NO_DEFAULT_PATH
  )  
  set( MODULE_SOURCE ${PROJECT_BINARY_DIR}/src/${MODULE}.cpp )
  set( LINKED_LIBRARIES ${ARGN} )
  set( MODULE_LD_CONFIGURATION "${PROJECT_BINARY_DIR}/ld.so.conf.d/${MODULE}.cfg" )
  set( MODULE_PYTHON_HELPER "${PROJECT_BINARY_DIR}/site-packages/${MODULE}.py" )
  add_custom_command( 
    OUTPUT ${MODULE_SOURCE} ${MODULE_LD_CONFIGURATION} ${MODULE_PYTHON_HELPER}
    DEPENDS ${${MODULE}_INFO}
    COMMAND ${INTERROGATE_MODULE_COMMAND}
      -oc ${MODULE_SOURCE}
      -module lib${MODULE} -library lib${MODULE}
      -python-native
      ${${MODULE}_INFO}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/ld.so.conf.d/
    COMMAND ${CMAKE_COMMAND} -E echo ${CMAKE_INSTALL_PREFIX}/lib/${MODULE} > ${MODULE_LD_CONFIGURATION}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/site-packages/
    COMMAND ${CMAKE_COMMAND} -E echo "import sys" > ${MODULE_PYTHON_HELPER} VERBATIM
    COMMAND ${CMAKE_COMMAND} -E echo "sys.path.append( \"${CMAKE_INSTALL_PREFIX}/lib/${MODULE}\" )" >> ${MODULE_PYTHON_HELPER} VERBATIM
    COMMAND ${CMAKE_COMMAND} -E echo "from lib${MODULE} import *" >> ${MODULE_PYTHON_HELPER}
    COMMENT   "Generating module '${MODULE}' from '${${MODULE}_INFO}'"
  )

  find_library( TOOL_LIB p3dtool /usr/lib/panda3d )
  find_library( TOOL_CONFIG_LIB p3dtoolconfig /usr/lib/panda3d )
  
  set( MODULE_LIB ${MODULE} )
  add_library( 
    ${MODULE_LIB} SHARED 
    ${MODULE_SOURCE}
    ${${MODULE}_SOURCES}
  )
  
  target_link_libraries( ${MODULE_LIB} ${TOOL_LIB} ${TOOL_CONFIG_LIB} ${LINKED_LIBRARIES} )

  install(
    TARGETS ${MODULE_LIB}
    LIBRARY DESTINATION lib/${MODULE} COMPONENT default
  )
  
  install(
    FILES ${MODULE_LD_CONFIGURATION} 
    DESTINATION ${CMAKE_INSTALL_ROOT}/etc/ld.so.conf.d/
    COMPONENT default
  )

  install(
    FILES ${MODULE_PYTHON_HELPER}
    DESTINATION ${CMAKE_INSTALL_ROOT}/${PYTHON_SITE_PACKAGES_PATH}
    COMPONENT default
  )
endmacro ( INTERROGATE_MODULE MODULE )

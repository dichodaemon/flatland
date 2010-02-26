project( flatland )

cmake_minimum_required( VERSION 2.6 )

set( PACKAGE_NAME ${PROJECT_NAME} )
set( PACKAGE_VERSION 0.0.1 )
set( PACKAGE_RELEASE 0 )
set( PACKAGE_MAINTAINER_NAME "Dizan Vasquez" )
set( PACKAGE_MAINTAINER_EMAIL "dizan@dizanvasquez.net" )
set( PACKAGE_DESCRIPTION_SUMMARY "2D Game engine" )
set( PACKAGE_DESCRIPTION "A complete 2D Game Engine with sound, graphics and physics" )
set( PACKAGE_DEPENDS )

include( SimpleCMake )
sm_configure_project()

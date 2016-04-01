#
# FAST Protect GmbH: osgworks
#
# History: 
# 2016-04-01  ARO  initial release

CMAKE_MINIMUM_REQUIRED(VERSION 3.4.0 FATAL_ERROR) 

# Include custom CMake modules or macros. Don't touch it.
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../buildtools/CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE(FastProtectMacros)

FAST_PROJECT(osgWorks)

FAST_IS_SYSTEM_LIBRARY(osgWorks OSGWORKS_IS_SYSTEM_LIB)

IF(NOT OSGWORKS_IS_SYSTEM_LIB)

	SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
	INCLUDE(OsgWMacroUtils)
	
	SET(OSGWORKS_SOVERSION 1)
	SET(OSGWORKS_VERSION_MAJOR 3)
	SET(OSGWORKS_VERSION_MINOR 0)
	SET(OSGWORKS_VERSION_PATCH 2)
	SET(OSGWORKS_VERSION_BUILD 0)
	
	# Note: These values are used by include/osgwTools/Version.in
	# to generate the Version.h file.
	set( OSGWORKS_VERSION ${OSGWORKS_VERSION_MAJOR}.${OSGWORKS_VERSION_MINOR}.${OSGWORKS_VERSION_PATCH} )
	set( OSGWORKS_MAJOR_VERSION ${OSGWORKS_VERSION_MAJOR} )
	set( OSGWORKS_MINOR_VERSION ${OSGWORKS_VERSION_MINOR} )
	set( OSGWORKS_SUB_VERSION ${OSGWORKS_VERSION_PATCH} )

	FAST_PACKAGE_OSG()
	FAST_PACKAGE_BOOST()
	if( Boost_FOUND )
		add_definitions( -DBOOST_FOUND )
		include_directories( ${Boost_INCLUDE_DIR} )
	endif()

	# find the optional Directx SDK (for DirectInput game pad support).
	#option( DIRECTINPUT_ARCH_x64 "Select for 64-bit target architectures, unselect for 32-bit." ON )
	#find_package( DirectInput QUIET )

	# find the optional VRPN library (for VRPN input support).
	#FAST_PACKAGE_VRPN()

	# Add OSG for entire project for include & lib paths
	INCLUDE_DIRECTORIES( 
		${PROJECT_SOURCE_DIR}/include
		${OSG_INCLUDE_DIRS}
	)


	option( OSGWORKS_BUILD_SHARED_LIBS "Set to ON to build osgWorks for dynamic linking. Use OFF for static." ON )
	if( NOT OSGWORKS_BUILD_SHARED_LIBS )
		add_definitions( -DOSGWORKS_STATIC )
	endif()

	OPTION( OSGWORKS_SCENEVIEW_ANAGLYPHIC_STEREO_SUPPORT "Enable to support OSG_STEREO=ON." OFF )
	IF( OSGWORKS_SCENEVIEW_ANAGLYPHIC_STEREO_SUPPORT )
		ADD_DEFINITIONS( -DSCENEVIEW_ANAGLYPHIC_STEREO_SUPPORT )
	ENDIF( OSGWORKS_SCENEVIEW_ANAGLYPHIC_STEREO_SUPPORT )


	option( OSGWORKS_BUILD_TESTS "Enable to build test code" OFF )
	if( OSGWORKS_BUILD_TESTS )
		enable_testing()
		add_definitions( -DOSGWORKS_BUILD_TESTS )
		add_subdirectory( tests )
	endif()

	OPTION( OSGWORKS_BUILD_APPS "Enable to build applications" ON )
	IF( OSGWORKS_BUILD_APPS )
		ADD_SUBDIRECTORY( apps )
	ENDIF( OSGWORKS_BUILD_APPS )

	option( OSGWORKS_BUILD_EXAMPLES "Enable to build example code" OFF )
	if( OSGWORKS_BUILD_EXAMPLES )
		ADD_SUBDIRECTORY( examples )
	endif()

	option( OSGWORKS_INSTALL_DATA "Enable to add the data directory to the install target" OFF )
	if( OSGWORKS_INSTALL_DATA )
		add_subdirectory( data )
	endif()


	ADD_SUBDIRECTORY( src )
		
	FAST_PROJECT_PACKAGE()

ENDIF(NOT OSGWORKS_IS_SYSTEM_LIB)

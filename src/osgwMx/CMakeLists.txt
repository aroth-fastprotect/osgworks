set( LIB_NAME osgwMx )

if( BUILD_SHARED_LIBS )
    add_definitions( -DOSGWMX_LIBRARY )
endif()


set( HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME} )

set( DX_DEPENDENT_HEADERS )
set( DX_DEPENDENT_SRC )
if( DIRECTINPUT_FOUND )
	add_definitions(-DDIRECTINPUT_ENABLED)
    include_directories( ${DIRECTINPUT_INCLUDE_DIR} )
    set( DX_DEPENDENT_HEADERS
        ${HEADER_PATH}/MxGamePadDX.h
    )
    set( DX_DEPENDENT_SRC
        MxGamePadDX.cpp
    )
endif()

set( VRPN_DEPENDENT_HEADERS )
set( VRPN_DEPENDENT_SRC )
if( VRPN_FOUND )
	add_definitions(-DVRPN_ENABLED)
    include_directories( ${VRPN_INCLUDES} )
    set( VRPN_DEPENDENT_HEADERS
        ${HEADER_PATH}/MxSpaceBallVRPN.h
    )
    set( VRPN_DEPENDENT_SRC
        MxSpaceBallVRPN.cpp
    )
endif() #VRPN_FOUND


set( TARGET_PUBLIC_H
    ${DX_DEPENDENT_HEADERS}
    ${VRPN_DEPENDENT_HEADERS}
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/CameraUpdateCallback.h
    ${HEADER_PATH}/MxCore.h
    ${HEADER_PATH}/MxEventHandler.h
    ${HEADER_PATH}/MxGamePad.h
    ${HEADER_PATH}/MxSpaceBall.h
    ${HEADER_PATH}/MxUtils.h
)

set( TARGET_SRC
    ${DX_DEPENDENT_SRC}
    ${VRPN_DEPENDENT_SRC}
    CameraUpdateCallback.cpp
    MxCore.cpp
    MxEventHandler.cpp
    MxGamePad.cpp
    MxSpaceBall.cpp
    MxUtils.cpp
)


SET(TARGET_LIBRARIES_VARS
	OSG_LIBRARY
	osgwTools
	)

if( DIRECTINPUT_FOUND )
	LIST(APPEND TARGET_LIBRARIES_VARS DIRECTINPUT_LIBRARIES)
endif()

if( VRPN_FOUND )
	LIST(APPEND TARGET_LIBRARIES_VARS VRPN_LIBRARY)
endif()

SETUP_OSG_LIB( ${LIB_NAME} )

set( LIB_NAME osgwControls )

if( OSGWORKS_BUILD_SHARED_LIBS )
    add_definitions( -DOSGWCONTROLS_LIBRARY )
endif()


set( HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME} )
set( TARGET_PUBLIC_H
    ${HEADER_PATH}/SliderControl.h
    ${HEADER_PATH}/Export.h
)

set( TARGET_SRC
    SliderControl.cpp
)

SET(TARGET_LIBRARIES_VARS
	OSG_LIBRARY
	OSGDB_LIBRARY
	OSGGA_LIBRARY
	OSGTEXT_LIBRARY
	OSGUTIL_LIBRARY
	OSGVIEWER_LIBRARY
	)

SET(TARGET_ADDED_LIBRARIES
	osgwTools
	)

SETUP_OSG_LIB(osgwControls)

set( LIB_NAME osgwQuery )

if( OSGWORKS_BUILD_SHARED_LIBS )
    add_definitions( -DOSGWQUERY_LIBRARY )
endif()


set( HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME} )
set( TARGET_PUBLIC_H
    ${HEADER_PATH}/QueryAPI.h
    ${HEADER_PATH}/QueryBenchmarks.h
    ${HEADER_PATH}/QueryComputation.h
    ${HEADER_PATH}/QueryObject.h
    ${HEADER_PATH}/QueryStats.h
    ${HEADER_PATH}/QueryUtils.h
    ${HEADER_PATH}/Export.h
)

set( TARGET_SRC
    QueryAPI.cpp
    QueryBenchmarks.cpp
    QueryComputation.cpp
    QueryObject.cpp
    QueryStats.cpp
    QueryUtils.cpp
)

SET(TARGET_LIBRARIES_VARS
	OSG_LIBRARY
	OSGGA_LIBRARY
	OSGUTIL_LIBRARY
	OSGTEXT_LIBRARY
	)

SET(TARGET_ADDED_LIBRARIES
	osgwTools
	)

SETUP_OSG_LIB( ${LIB_NAME} )


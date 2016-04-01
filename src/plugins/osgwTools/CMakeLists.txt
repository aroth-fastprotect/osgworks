
SET(TARGET_SRC 
    dotosgAbsoluteModelTransform.cpp
    dotosgCameraConfigObject.cpp
    dotosgFunctionalMap.cpp
    dotosgRefID.cpp
	)

SET(TARGET_LIBRARIES_VARS
	OSG_LIBRARY
	OSGDB_LIBRARY
	)

SET(TARGET_ADDED_LIBRARIES
	osgwTools
	)

SETUP_PLUGIN( osgwTools )

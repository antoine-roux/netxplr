# - Find DL
#
# -*- cmake -*-
#
# Find the DL module
#
# DL_INCLUDE_DIR  - Where to find dlfcn.h.
# DL_LIBRARIES    - List of libraries when using DL.
# DL_FOUND        - True if DL found.
 
IF (DL_INCLUDE_DIR)
	# Already in cache, be silent
	SET(DL_FIND_QUIETLY TRUE)
ENDIF (DL_INCLUDE_DIR)
 
FIND_PATH(DL_INCLUDE_DIR NAMES dlfcn.h)
FIND_LIBRARY(DL_LIBRARY NAMES dl)
 
SET(DL_LIBRARIES
	${DL_LIBRARY}
)
 
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DL
	DEFAULT_MSG
	DL_INCLUDE_DIR
	DL_LIBRARIES
)
 
MARK_AS_ADVANCED(
	DL_LIBRARY
	DL_INCLUDE_DIR
) 

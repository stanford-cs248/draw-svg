# Find CS248 library and include paths
# This defines the following:
#
# CS248_FOUND             If CS248 is found
# CS248_LIBRARIES         CS248 libraries
# CS248_INCLUDE_DIRS      CS248 include directories
# CS248_LIBRARY_DIRS      CS248 library directories

if(UNIX)
  set(CS248_INC_NAMES CS248.h)
  set(CS248_LIB_NAMES libCS248.a)
  if(APPLE)
    set(CS248_LIB_NAMES libCS248_osx.a)
  endif(APPLE)
endif(UNIX)

# CS248 static library
find_library(CS248_LIBRARIES
    NAMES ${CS248_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/../lib
    DOC "CS248 library")

# CS248 library dir
find_path(CS248_LIBRARY_DIRS
    NAMES ${CS248_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/../lib
    DOC "462 include directories")

# CS248 include dir
find_path(CS248_INCLUDE_DIRS
    NAMES ${CS248_INC_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/../include/
    DOC "462 include directories")

# Version
set(CS248_VERSION 1.0)

# Set package standard args
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CS248 
    REQUIRED_VARS CS248_INCLUDE_DIRS CS248_LIBRARY_DIRS CS248_LIBRARIES
    VERSION_VAR CS248_VERSION)

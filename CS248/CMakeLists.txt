cmake_minimum_required(VERSION 2.8)
project(CS248)

#-------------------------------------------------------------------------------
# Build options
#-------------------------------------------------------------------------------
option(CS248_BUILD_DEBUG    "Build for debug"          OFF)
option(CS248_BUILD_SHARED   "Build shared libraries"   OFF)
option(CS248_BUILD_DOCS     "Build documentation"      OFF)
option(CS248_BUILD_TESTS    "Build tests programs"     OFF)
option(CS248_BUILD_EXAMPLES "Build examples"           OFF)

#-------------------------------------------------------------------------------
# CMake modules
#-------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CS248_SOURCE_DIR}/cmake/modules/")

#-------------------------------------------------------------------------------
# CS248 paths
#-------------------------------------------------------------------------------
set(CS248_INCLUDE_DIRS "${CS248_SOURCE_DIR}/include" "${CS248_SOURCE_DIR}/include/CS248")

#-------------------------------------------------------------------------------
# Platform-specific settings
#-------------------------------------------------------------------------------

###################
# Building on OSX #
###################
if(APPLE)

  # Clang only
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")

    # OSX Framework dependencies
    if(NOT CS248_BUILD_SHARED)
      include_directories( "/System/Library/Frameworks" )
      find_library (COCOA_LIBRARIES Cocoa)
      find_library (IOKIT_LIBRARIES IOkit)
      find_library (COREVIDEO_LIBRARIES CoreVideo)
    endif()

    # Clang configuration
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

      set(CLANG_CXX_FLAGS "-std=c++11 -m64")

      if(CS248_BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE Debug)
      else(CS248_BUILD_DEBUG)
        set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -O3")
        set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -funroll-loops")
        set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-narrowing")
        set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-register")
      endif(CS248_BUILD_DEBUG)

      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")

    endif()

    # GCC configuration
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

      set(GCC_CXX_FLAGS "-std=gnu++11 -m64")

      if(CS248_BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE Debug)
      else(CS248_BUILD_DEBUG)
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -O3")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -fopenmp")
      endif(CS248_BUILD_DEBUG)

      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")

    endif()

  endif()

endif(APPLE)

##################
# Build on Linux #
##################
set(LINUX UNIX AND NOT APPLE)
if(LINUX)

  # GCC only
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

    set(GCC_CXX_FLAGS "-std=gnu++11 -m64")

    # X11 Dependencies
    if(NOT CS248_BUILD_SHARED)
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXi")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXxf86vm")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXinerama")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXcursor")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXfixes")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrandr")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXext")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrender")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lX11")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lpthread")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lxcb")
      set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXau")
    endif()

    # Debug configuration
    if(CS248_BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE Debug)
    else(CS248_BUILD_DEBUG)
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -O3")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -fopenmp")
    endif(CS248_BUILD_DEBUG)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")

  endif()

endif(LINUX)

####################
# Build on Windows #
####################
if(WIN32)

  if(MSVC)

    set(MSVC_CXX_FLAGS "-std=gnu++11")

    if(CS248_BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE Debug)
    else(CS248_BUILD_DEBUG)
    endif(CS248_BUILD_DEBUG)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

    add_subdirectory("${CS248_SOURCE_DIR}/deps/freetype")
    if(CS248_BUILD_THREADED)
        add_subdirectory("${CS248_SOURCE_DIR}/deps/pthread")
    endif(CS248_BUILD_THREADED)

  endif(MSVC)

  if(MINGW)

    set(MSVC_CXX_FLAGS "-std=gnu++11")

    if(CS248_BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE Debug)
    else(CS248_BUILD_DEBUG)
    endif(CS248_BUILD_DEBUG)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

  endif(MINGW)

endif(WIN32)

#-------------------------------------------------------------------------------
# Find dependencies
#-------------------------------------------------------------------------------

# Required packages
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
if(NOT WIN32)
  find_package(Freetype REQUIRED)
endif()

# Use pkg-config for GLEW & GLFW if available
find_package(PkgConfig QUIET)

# GLEW
if(PKGCONFIG_FOUND)
  pkg_search_module(GLEW QUIET GLEW)
else(PKGCONFIG_FOUND)
  find_package(GLEW QUIET)
endif()
if(NOT GLEW_FOUND)
  add_subdirectory("${CS248_SOURCE_DIR}/deps/glew")
  set_property( TARGET glew APPEND_STRING PROPERTY COMPILE_FLAGS -w )
endif()

# GLFW
if(PKGCONFIG_FOUND)
  pkg_search_module(GLFW QUIET glfw3)
else(PKGCONFIG_FOUND)
  find_package(GLFW QUIET)
endif()
if(NOT GLFW_FOUND)
  add_subdirectory("${CS248_SOURCE_DIR}/deps/glfw")
  set_property( TARGET glfw APPEND_STRING PROPERTY COMPILE_FLAGS -w )
endif()

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
  ${CS248_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${PTHREAD_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
  ${GLEW_LIBRARY_DIRS}
  ${GLFW_LIBRARY_DIRS}
  ${FREETYPE_LIBRARY_DIRS}
  ${PTHREAD_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Add subdirectories
#-------------------------------------------------------------------------------

# CS248 library source directory
add_subdirectory(src)

# CS248 tests source directory
if(CS248_BUILD_TESTS)
  add_subdirectory(tests)
endif()

# CS248 exmaples source directory
if(CS248_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# CS248 documentation directory
if(CS248_BUILD_DOCS)
  find_package(DOXYGEN)
  if(DOXYGEN_FOUND AND CS248_BUILD_DOCS)
    add_subdirectory(docs)
  endif()
endif()

#-------------------------------------------------------------------------------
# Packing
#-------------------------------------------------------------------------------

# Install settings
set(CMAKE_INSTALL_PREFIX "${CS248_SOURCE_DIR}")

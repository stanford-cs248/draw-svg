cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/include/CS248)

# CS248 library source files
set(CS248_SOURCE
    vector2D.cpp
    vector3D.cpp
    vector4D.cpp
    matrix3x3.cpp
    matrix4x4.cpp
    quaternion.cpp
    complex.cpp
    color.cpp
    spectrum.cpp
    osdtext.cpp
    osdfont.cpp
    viewer.cpp
    base64.cpp
    lodepng.cpp
    tinyxml2.cpp
)

#-------------------------------------------------------------------------------
# Building static library (always)
#-------------------------------------------------------------------------------
add_library(CS248 STATIC ${CS248_SOURCE})

target_link_libraries(
  CS248
  ${GLEW_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${FREETYPE_LIBRARIES}
)

#-------------------------------------------------------------------------------
# Building shared library
#-------------------------------------------------------------------------------
if(CS248_BUILD_SHARED)
  add_library(CS248_SHARED SHARED ${CS248_SOURCE})
  target_link_libraries(
    CS248_SHARED
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES}
  )
endif()

#-------------------------------------------------------------------------------
# Platform-specific target configurations
#-------------------------------------------------------------------------------

###################
# Building on OSX #
###################
if (APPLE)

  # Clang options
  target_compile_options(CS248 PRIVATE -Wno-constant-conversion)

  # Framework dependencies
  target_link_libraries(CS248
    ${COCOA_LIBRARIES}
    ${IOKIT_LIBRARIES}
    ${COREVIDEO_LIBRARIES})

  # Output name
  if(CS248_BUILD_DEBUG)
    set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248_osx_d)
    if(CS248_BUILD_SHARED)
      set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248_osx_d)
    endif()
  else(CS248_BUILD_DEBUG)
    set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248_osx)
    if(CS248_BUILD_SHARED)
      set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248_osx)
    endif()
  endif(CS248_BUILD_DEBUG)

endif(APPLE)

##################
# Build on Linux #
##################
set(LINUX UNIX AND NOT APPLE)
if(LINUX)
  if(CS248_BUILD_DEBUG)
    set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248_d)
    if(CS248_BUILD_SHARED)
      set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248_d)
    endif()
  else(CS248_BUILD_DEBUG)
    set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248)
    if(CS248_BUILD_SHARED)
      set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248)
    endif()
  endif(CS248_BUILD_DEBUG)
endif(LINUX)

####################
# Build on Windows #
####################
if(WIN32)

  if(MSVC)
    if(CS248_BUILD_DEBUG)
      set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248_d)
      if(CS248_BUILD_SHARED)
        set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248_d)
      endif()
    else(CS248_BUILD_DEBUG)
      set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248)
      if(CS248_BUILD_SHARED)
        set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248)
      endif()
    endif(CS248_BUILD_DEBUG)
  endif(MSVC)

  if(MINGW)
    if(CS248_BUILD_DEBUG)
      set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248_d)
      if(CS248_BUILD_SHARED)
        set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248_d)
      endif()
    else(CS248_BUILD_DEBUG)
      set_target_properties(CS248 PROPERTIES OUTPUT_NAME CS248)
      if(CS248_BUILD_SHARED)
        set_target_properties(CS248_SHARED PROPERTIES OUTPUT_NAME CS248)
      endif()
    endif(CS248_BUILD_DEBUG)
  endif(MINGW)

endif(WIN32)

#-------------------------------------------------------------------------------
# Installation configurations
#-------------------------------------------------------------------------------
install(TARGETS CS248 DESTINATION lib)
if(CS248_BUILD_SHARED)
  install(TARGETS CS248_SHARED DESTINATION lib)
endif()

# install headers
install(FILES ${CS248_HEADER} DESTINATION include/CS248)

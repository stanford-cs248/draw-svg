set(DRAWSVG_BUILD_REFERENCE OFF)

if(DRAWSVG_BUILD_REFERENCE)

  # Build reference
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  # drawsvg reference source
  set(CS248_DrawSVGREF_SOURCE
      reference/viewport.cpp
      reference/texture.cpp
      reference/software_renderer.cpp
  )

  # drawsvg reference lib
  add_library( drawsvg_ref STATIC
      ${CS248_DrawSVGREF_SOURCE}
  )
  
    add_library( drawsvg_ref-debug STATIC
        ${CS248_DrawSVGREF_SOURCE}
    )
  
  # output name
  if (UNIX)
    set_target_properties(drawsvg_ref PROPERTIES OUTPUT_NAME drawsvgref)
    if(APPLE)
      set_target_properties(drawsvg_ref PROPERTIES OUTPUT_NAME drawsvgref_osx)
    endif(APPLE)
  endif(UNIX)
  install(TARGETS drawsvg_ref DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/reference)

else(DRAWSVG_BUILD_REFERENCE)

  add_library( drawsvg_ref STATIC IMPORTED)
  add_library( drawsvg_ref-debug STATIC IMPORTED)

  # Import reference
  if (UNIX)
    if(CS248_BUILD_THREADED)
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/libdrawsvgref_threaded.a)
	else()
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/libdrawsvgref.a)

		set_property(TARGET drawsvg_ref-debug PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/libdrawsvgref.a)



	endif()
  endif(UNIX)

  if(APPLE)
    if(CS248_BUILD_THREADED)
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/libdrawsvgref_threaded_osx.a)
	else()
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/libdrawsvgref_osx.a)
	endif()
  endif(APPLE)

  if(WIN32)
    if(CS248_BUILD_THREADED)
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/drawsvg_ref_threaded.lib)
		set_property(TARGET drawsvg_ref-debug PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/drawsvg_ref_threaded-debug.lib)
	else()
		set_property(TARGET drawsvg_ref PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/drawsvg_ref.lib)
		set_property(TARGET drawsvg_ref-debug PROPERTY IMPORTED_LOCATION
					${CMAKE_CURRENT_SOURCE_DIR}/reference/drawsvg_ref-debug.lib)
    endif()
  endif(WIN32)

endif(DRAWSVG_BUILD_REFERENCE)

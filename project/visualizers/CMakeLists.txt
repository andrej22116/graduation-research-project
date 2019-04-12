cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( TargetSceneVisualizer )

set( CPP_SOURCES
	TargetSceneRendererFactory.cpp
)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

add_library( visualizers SHARED
  ${CPP_SOURCES}
)
add_library( TargetSceneVisualizer::visualizers ALIAS visualizers )

target_link_libraries( visualizers
  PUBLIC
#	nodes
)

target_compile_options( visualizers
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
)

set_target_properties( visualizers
  PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
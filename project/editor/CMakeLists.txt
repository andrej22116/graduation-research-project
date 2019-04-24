cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( ShaderLogickNodeEditor )

set( CPP_SOURCES
	FunctionalNodes.cpp
	nodesstore/NodeWidget.cpp
	nodesstore/FlowLayout.cpp
	EditorGraphicsScene.cpp
)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

add_library( editor SHARED
  ${CPP_SOURCES}
)
add_library( ShaderLogickNodeEditor::editor ALIAS editor )

target_link_libraries( editor
  PUBLIC
	nodes
)

set(CMAKE_AUTOMOC ON)

target_compile_options( editor
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
)

set_target_properties( editor
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bin
)

add_subdirectory( nodeeditor )

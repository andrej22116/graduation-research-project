cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( ShaderLogickNodeEditor )

set( CPP_SOURCES
	FunctionalNodes.cpp
)

add_library( editor SHARED
  ${CPP_SOURCES}
)
add_library( ShaderLogickNodeEditor::editor ALIAS editor )

target_link_libraries( editor
  PUBLIC
	nodes
)

set_target_properties( editor
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_subdirectory( nodeeditor )
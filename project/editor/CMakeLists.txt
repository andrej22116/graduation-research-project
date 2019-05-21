cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( ShaderLogickNodeEditor )

set( CPP_SOURCES
	FunctionalNodes.cpp
        VariableNodes.cpp
	nodesstore/NodeWidget.cpp
	nodesstore/FlowLayout.cpp
	EditorGraphicsScene.cpp
        VariableWidgets.cpp
        VariableValueControlsFactory.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
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
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

add_subdirectory( nodeeditor )

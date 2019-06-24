cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( ShaderLogickNodeEditor )

set( CPP_SOURCES
        EditorController.cpp
        EditorGraphicsScene.cpp

        nodes/VariableNode/VariableNode.cpp
        nodes/VariableNode/VariableNodePainterDelegate.cpp
        nodes/ConstVariables/ConstVariablesNodes.cpp
        nodes/FunctionalNodes.cpp
        nodes/DataTypeInteractionRules.cpp
        nodes/LogickalNodes.cpp
        nodes/CommonFunctionalNodes.cpp
        nodes/GeometrycFunctionalNodes.cpp

        nodesmodels/DefaultDataModelRegistry.cpp

	nodesstore/NodeWidget.cpp
	nodesstore/FlowLayout.cpp
        nodesstore/NodeStoreWidget.cpp

        variablescontroller/VariablesListWidget.cpp
        variablescontroller/VariablesControllerWidget.cpp
        variablescontroller/VariablesController.cpp
        variablescontroller/VariableDataModelsFactory.cpp
        variablescontroller/VariablesEditorWidget.cpp
        variablescontroller/VariableValueEditorsFactory.cpp
        variablescontroller/VariableValueEditors.cpp
        variablescontroller/NodeDataTypeFactory.cpp
        variablescontroller/NodeDataTypeSerializer.cpp

        variableconverters/VectorConverter/VectorConnectGraphicsItem.cpp
        variableconverters/VectorConverter/VectorConverterScene.cpp
        variableconverters/VectorConverter/VectorConverterStyle.cpp
        variableconverters/VectorConverter/VectorConverterWidget.cpp
        variableconverters/VectorConverter/VectorPointGraphicsItem.cpp
        variableconverters/VectorConverter/VectorConverterDataModel.cpp

        variableconverters/VectorDecomposConverter/VectorDecomposConverter.cpp
        variableconverters/BaseTypesConverters/BaseTypesConverters.cpp
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

target_compile_definitions( editor
  PRIVATE
    SHARED_LIBRARY
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

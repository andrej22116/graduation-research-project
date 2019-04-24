cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( TargetSceneVisualizer )

set( CPP_SOURCES
#	TargetSceneRendererFactory.cpp
        LookCentralObjectCamera.cpp
        OpenGLScene.cpp
        TargetObject.cpp
)

set( QT_SRC
    ./resources/src.qrc
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

add_library( visualizers SHARED
  ${CPP_SOURCES}
  ${QT_SRC}
)
add_library( TargetSceneVisualizer::visualizers ALIAS visualizers )

# Libraries #
find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
)

target_link_libraries( visualizers
  PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

include_directories( visualizers
    ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include
)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
target_link_libraries(visualizers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/assimp/lib/libassimp.dll.a
)
else("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
target_link_libraries(visualizers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/assimp/lib/assimp-vc140-mt.lib
)
endif()


set_target_properties( visualizers
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

########################
#
# MOC MOC MOC MOC
#
########################

file(GLOB_RECURSE HEADERS_TO_MOC ./visualizers/*.hpp)

qt5_wrap_cpp( visualizers_moc
    ${HEADERS_TO_MOC}
  TARGET visualizers
  OPTIONS --no-notes # Don't display a note for the headers which don't produce a moc_*.cpp
)

target_sources(visualizers PRIVATE ${visualizers_moc})

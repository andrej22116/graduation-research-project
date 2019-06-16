cmake_minimum_required( VERSION 3.14.0 FATAL_ERROR )
project( SourceCompilersController )

set( CPP_SOURCES
    ICompiler.cpp
    CompilerController.cpp
    CompilerWrapper.cpp
    DefaultGlslCompiler/DefaultGlslCompiler.cpp
    test.cpp
)

set( QT_SRC
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

#add_library( compilers SHARED
add_executable( SourceCompilersController #compilers
  ${CPP_SOURCES}
  ${QT_SRC}
)
#add_library( SourceCompilersController::compilers ALIAS compilers )

# Libraries #
find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    Concurrent
)

target_link_libraries( SourceCompilersController #compilers
  PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)


set_target_properties( SourceCompilersController #compilers
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

########################
#
# MOC MOC MOC MOC
#
########################

file(GLOB_RECURSE HEADERS_TO_MOC ./compilers/*.hpp)

qt5_wrap_cpp( compilers_moc
    ${HEADERS_TO_MOC}
  TARGET SourceCompilersController #compilers
  OPTIONS --no-notes # Don't display a note for the headers which don't produce a moc_*.cpp
)

target_sources(SourceCompilersController PRIVATE ${compilers_moc})

cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(MultilingualShaderDesigner LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(project_ui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(project_sources main.cpp)
set( project_resources
    ./resources/resources.qrc
    ./resources/resources.rc
)

add_executable(${PROJECT_NAME}
#    WIN32
#    ${project_headers}
    ${project_sources}
    ${project_sources_moc}
    ${project_headers_wrapped}
    ${project_resources}
)

add_subdirectory(editor)
add_subdirectory(visualizers)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    editor
    visualizers
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bin
)

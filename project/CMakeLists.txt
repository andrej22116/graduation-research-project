cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(MultilingualShaderDesigner LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

set(project_ui)

set(project_headers)

set(project_sources
        src/main.cpp
)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
qt5_wrap_cpp(project_sources_moc ${project_headers})

add_executable(${PROJECT_NAME}
    ${project_headers}
    ${project_sources}
    ${project_sources_moc}
    ${project_headers_wrapped}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    nodes
)


add_subdirectory(dependencies)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

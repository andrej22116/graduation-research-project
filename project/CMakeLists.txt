cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(MultilingualShaderDesigner LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

set(project_ui)

#target_include_directories(${PROJECT_NAME} PUBLIC ./include)
#set (CMAKE_INCLUDE_PATH ./include)
#set(project_headers)
#file(GLOB_RECURSE ${project_headers} ./include/*.hpp)

set(project_sources main.cpp)
#file(GLOB ${project_sources} ./src/*.cpp)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
#qt5_wrap_cpp(project_sources_moc ${project_headers})

add_executable(${PROJECT_NAME}
#    WIN32
#    ${project_headers}
    ${project_sources}
    ${project_sources_moc}
    ${project_headers_wrapped}
)

add_subdirectory(editor)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    editor
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

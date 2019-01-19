cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(MultilingualShaderDesigner LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

set(project_ui)

set(project_headers

#   Model shader node type classes
    src/ShaderNodes/Model/Types/ClassColorNodeModel/ColorNodeModel.hpp
    src/ShaderNodes/Model/Types/ClassDoubleNodeModel/DoubleNodeModel.hpp
    src/ShaderNodes/Model/Types/ClassFloatNodeModel/FloatNodeModel.hpp
    src/ShaderNodes/Model/Types/ClassInt16NodeModel/Int16NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassInt32NodeModel/Int32NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassMatrix3NodeModel/Matrix3NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassMatrix4NodeModel/Matrix4NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassSamplerNodeModel/SamplerNodeModel.hpp
    src/ShaderNodes/Model/Types/ClassVector2NodeModel/Vector2NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassVector3NodeModel/Vector3NodeModel.hpp
    src/ShaderNodes/Model/Types/ClassVector4NodeModel/Vector4NodeModel.hpp
    src/ShaderNodes/ColorNodeModel
    src/ShaderNodes/DoubleNodeModel
    src/ShaderNodes/FloatNodeModel
    src/ShaderNodes/Int16NodeModel
    src/ShaderNodes/Int32NodeModel
    src/ShaderNodes/Matrix3NodeModel
    src/ShaderNodes/Matrix4NodeModel
    src/ShaderNodes/SamplerNodeModel
    src/ShaderNodes/Vector2NodeModel
    src/ShaderNodes/Vector3NodeModel
    src/ShaderNodes/Vector4NodeModel

#   Data shader node type classes
    src/ShaderNodes/Data/ClassColorData/ColorData.hpp
    src/ShaderNodes/Data/ClassDoubleData/DoubleData.hpp
    src/ShaderNodes/Data/ClassFloatData/FloatData.hpp
    src/ShaderNodes/Data/ClassInt16Data/Int16Data.hpp
    src/ShaderNodes/Data/ClassInt32Data/Int32Data.hpp
    src/ShaderNodes/Data/ClassMatrix3Data/Matrix3Data.hpp
    src/ShaderNodes/Data/ClassMatrix4Data/Matrix4Data.hpp
    src/ShaderNodes/Data/ClassSamplerData/SamplerData.hpp
    src/ShaderNodes/Data/ClassVector2Data/Vector2Data.hpp
    src/ShaderNodes/Data/ClassVector3Data/Vector3Data.hpp
    src/ShaderNodes/Data/ClassVector4Data/Vector4Data.hpp
    src/ShaderNodes/ColorData
    src/ShaderNodes/DoubleData
    src/ShaderNodes/FloatData
    src/ShaderNodes/Int16Data
    src/ShaderNodes/Int32Data
    src/ShaderNodes/Matrix3Data
    src/ShaderNodes/Matrix4Data
    src/ShaderNodes/SamplerData
    src/ShaderNodes/Vector2Data
    src/ShaderNodes/Vector3Data
    src/ShaderNodes/Vector4Data
    src/ShaderNodes/Data/ClassDataConverter/DataConverter.hpp

#   Function shader node type classes
    src/ShaderNodes/Model/Functions/ClassFunctionAbsNodeModel/FunctionAbsNodeModel.hpp
)

set(project_sources
    src/main.cpp

#   Model shader node type classes
    src/ShaderNodes/Model/Types/ClassColorNodeModel/ColorNodeModel.cpp
    src/ShaderNodes/Model/Types/ClassDoubleNodeModel/DoubleNodeModel.cpp
    src/ShaderNodes/Model/Types/ClassFloatNodeModel/FloatNodeModel.cpp
    src/ShaderNodes/Model/Types/ClassInt16NodeModel/Int16NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassInt32NodeModel/Int32NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassMatrix3NodeModel/Matrix3NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassMatrix4NodeModel/Matrix4NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassSamplerNodeModel/SamplerNodeModel.cpp
    src/ShaderNodes/Model/Types/ClassVector2NodeModel/Vector2NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassVector3NodeModel/Vector3NodeModel.cpp
    src/ShaderNodes/Model/Types/ClassVector4NodeModel/Vector4NodeModel.cpp

#   Data shader node type classes
    src/ShaderNodes/Data/ClassColorData/ColorData.cpp
    src/ShaderNodes/Data/ClassDoubleData/DoubleData.cpp
    src/ShaderNodes/Data/ClassFloatData/FloatData.cpp
    src/ShaderNodes/Data/ClassInt16Data/Int16Data.cpp
    src/ShaderNodes/Data/ClassInt32Data/Int32Data.cpp
    src/ShaderNodes/Data/ClassMatrix3Data/Matrix3Data.cpp
    src/ShaderNodes/Data/ClassMatrix4Data/Matrix4Data.cpp
    src/ShaderNodes/Data/ClassSamplerData/SamplerData.cpp
    src/ShaderNodes/Data/ClassVector2Data/Vector2Data.cpp
    src/ShaderNodes/Data/ClassVector3Data/Vector3Data.cpp
    src/ShaderNodes/Data/ClassVector4Data/Vector4Data.cpp
    src/ShaderNodes/Data/ClassDataConverter/DataConverter.cpp

#   Function shader node type classes
    src/ShaderNodes/Model/Functions/ClassFunctionAbsNodeModel/FunctionAbsNodeModel.cpp
)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
#qt5_wrap_cpp(project_sources_moc ${project_headers})

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

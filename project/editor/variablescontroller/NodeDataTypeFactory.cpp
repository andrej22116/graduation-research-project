#include "NodeDataTypeFactory.hpp"
#include "ShaderNodeDataTypes.hpp"
#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;

NodeDataTypeFactory::NodeDataTypeFactory()
{
    registerDataType<IntegerDataType>();
    registerDataType<UnsignedIntegerDataType>();
    registerDataType<BooleanDataType>();
    registerDataType<FloatDataType>();
    registerDataType<DoubleDataType>();
    registerDataType<Vec2DataType>();
    registerDataType<Vec3DataType>();
    registerDataType<Vec4DataType>();
    registerDataType<Matrix2DataType>();
    registerDataType<Matrix3DataType>();
    registerDataType<Matrix4DataType>();
    registerDataType<IntegerVec2DataType>();
    registerDataType<IntegerVec3DataType>();
    registerDataType<IntegerVec4DataType>();
    registerDataType<DoubleVec2DataType>();
    registerDataType<DoubleVec3DataType>();
    registerDataType<DoubleVec4DataType>();
    registerDataType<UnsignedIntegerVec2DataType>();
    registerDataType<UnsignedIntegerVec3DataType>();
    registerDataType<UnsignedIntegerVec4DataType>();
    registerDataType<DoubleMatrix2DataType>();
    registerDataType<DoubleMatrix3DataType>();
    registerDataType<DoubleMatrix4DataType>();
    registerDataType<Texture2D_DataType>();
}


NodeDataType
NodeDataTypeFactory::
build(const QString& name)
{
    return instance()._dataTypes[name];
}


const QSet<QString>&
NodeDataTypeFactory::
supportedTypes()
{
    return instance()._supportedTypes;
}


NodeDataTypeFactory&
NodeDataTypeFactory::instance()
{
    static NodeDataTypeFactory factory;
    return factory;
}

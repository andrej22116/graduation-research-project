#include "VariableDataModelsFactory.hpp"
#include <ShaderNodeDataTypes.hpp>

VariableDataModelsFactory::
VariableDataModelsFactory()
{
    registerDataType<IntegerDataType, IntegerDataModel>();
    registerDataType<UnsignedIntegerDataType, UnsignedIntegerDataModel>();
    registerDataType<BooleanDataType, BooleanDataModel>();
    registerDataType<FloatDataType, FloatDataModel>();
    registerDataType<DoubleDataType, DoubleDataModel>();
    registerDataType<Vec2DataType, Vec2DataModel>();
    registerDataType<Vec3DataType, Vec3DataModel>();
    registerDataType<Vec4DataType, Vec4DataModel>();
    registerDataType<Matrix2DataType, Mat2x2DataModel>();
    registerDataType<Matrix3DataType, Mat3x3DataModel>();
    registerDataType<Matrix4DataType, Mat4x4DataModel>();
}

#include <QDebug>
VariableDataModelsFactory::VariableDataModelPtr
VariableDataModelsFactory::
build(const QString& name)
{
    return std::dynamic_pointer_cast<VariableDataModel>(
                    instance()._varFactories[name]()
                );
}


const QSet<QString>&
VariableDataModelsFactory::
supportedTypes()
{
    return instance()._supportedTypes;
}


VariableDataModelsFactory&
VariableDataModelsFactory::
instance()
{
    static VariableDataModelsFactory instance;
    return instance;
}

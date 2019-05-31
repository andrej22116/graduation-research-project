#include "VariableDataModelsFactory.hpp"
#include <editor/ShaderNodeDataTypes.hpp>

VariableDataModelsFactory::
VariableDataModelsFactory()
{
    {
        IntegerDataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<IntegerDataModel>();
        };
    }

    {
        UnsignedIntegerDataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<UnsignedIntegerDataModel>();
        };
    }

    {
        BooleanDataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<BooleanDataModel>();
        };
    }

    {
        FloatDataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<FloatDataModel>();
        };
    }

    {
        DoubleDataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<DoubleDataModel>();
        };
    }

    {
        Vec2DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Vec2DataModel>();
        };
    }

    {
        Vec3DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Vec3DataModel>();
        };
    }

    {
        Vec4DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Vec4DataModel>();
        };
    }

    {
        Matrix2DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Mat2x2DataModel>();
        };
    }

    {
        Matrix3DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Mat3x3DataModel>();
        };
    }

    {
        Matrix4DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<Mat4x4DataModel>();
        };
    }
}


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

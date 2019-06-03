#include "VariableValueEditorsFactory.hpp"
#include "VariableValueEditors.hpp"
#include "ShaderNodeDataTypes.hpp"

VariableValueEditorsFactory::
VariableValueEditorsFactory()
{
    registerDataType<IntegerDataType, IntegerValueEditor>();
    registerDataType<UnsignedIntegerDataType, UnsignedIntegerValueEditor>();
    registerDataType<FloatDataType, FloatValueEditor>();
    registerDataType<DoubleDataType, DoubleValueEditor>();
    registerDataType<BooleanDataType, BooleanValueEditor>();
}

VariableValueEditor*
VariableValueEditorsFactory::
build(const QString& modelDataTypeName)
{
    return instance()._variableEditors[modelDataTypeName]();
}

const QSet<QString>&
VariableValueEditorsFactory::
supportedTypes()
{
    return instance()._supportedTypes;
}

VariableValueEditorsFactory&
VariableValueEditorsFactory::
instance()
{
    static VariableValueEditorsFactory instance;
    return instance;
}

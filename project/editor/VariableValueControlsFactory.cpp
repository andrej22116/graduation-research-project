#include "VariableValueControlsFactory.hpp"

#include <QWidget>
#include <QGridLayout>

#include "VariableWidgets.hpp"
#include "ShaderNodeDataTypes.hpp"

#include <QIntValidator>
#include <QDoubleValidator>
#include <cinttypes>
#include <cfloat>

VariableValueControlsFactory::VariableValueControlsFactory()
{
    _mapOfFactories[IntegerDataType{}.id] = [](QWidget* parent){
        return new SingleValueVariableWidget(new QIntValidator(INT32_MIN, INT32_MAX), parent);
    };
    _mapOfFactories[UnsignedIntegerDataType{}.id] = [](QWidget* parent){
        return new SingleValueVariableWidget(new QIntValidator(0, UINT32_MAX), parent);
    };
    _mapOfFactories[DoubleDataType{}.id] = [](QWidget* parent){
        return new SingleValueVariableWidget(new QDoubleValidator(DBL_MIN, DBL_MAX, 12), parent);
    };
    _mapOfFactories[FloatDataType{}.id] = [](QWidget* parent){
        return new SingleValueVariableWidget(new QDoubleValidator(FLT_MIN, FLT_MAX, 6), parent);
    };
    _mapOfFactories[BooleanDataType{}.id] = [](QWidget* parent){
        return new BooleanVariableWidget(parent);
    };
    _mapOfFactories[Vec2DataType{}.id] = [](QWidget* parent){
        return new Vec2VariableWidget(nullptr, parent);
    };
    _mapOfFactories[Vec3DataType{}.id] = [](QWidget* parent){
        return new Vec3VariableWidget(nullptr, parent);
    };
    _mapOfFactories[Vec4DataType{}.id] = [](QWidget* parent){
        return new Vec4VariableWidget(nullptr, parent);
    };
    _mapOfFactories[Matrix2DataType{}.id] = [](QWidget* parent){
        return new Matrix2VariableWidget(nullptr, parent);
    };
    _mapOfFactories[Matrix3DataType{}.id] = [](QWidget* parent){
        return new Matrix3VariableWidget(nullptr, parent);
    };
    _mapOfFactories[Matrix4DataType{}.id] = [](QWidget* parent){
        return new Matrix4VariableWidget(nullptr, parent);
    };
}

VariableWidget* VariableValueControlsFactory::makeWidget( const QString& typeName
                                                        , QWidget* parent)
{
    static VariableValueControlsFactory factory;
    return factory._mapOfFactories[typeName](parent);
}

#include "BaseTypesConverters.hpp"
#include "ShaderNodeDataTypes.hpp"
#include <nodes/Connection>

QSet<QString> PrimitiveNodeTypeConverter::_supportedTypes = {
    IntegerDataType{}.id,
    UnsignedIntegerDataType{}.id,
    DoubleDataType{}.id,
    FloatDataType{}.id,
};

QString
PrimitiveNodeTypeConverter::
caption() const
{
    return _caption;
}


QString
PrimitiveNodeTypeConverter::
name() const
{
    return _name;
}


unsigned int
PrimitiveNodeTypeConverter::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
PrimitiveNodeTypeConverter::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::In ) {
        return _inDataType;
    }

    return _outDataType;
}


bool
PrimitiveNodeTypeConverter::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    return _supportedTypes.find(nodeDataType.id) != _supportedTypes.end();
}


QJsonObject
PrimitiveNodeTypeConverter::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj["from"] = _inDataType.id;

    return obj;
}


void
PrimitiveNodeTypeConverter::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _inDataType = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
PrimitiveNodeTypeConverter::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _inDataType = NO_DATA_TYPE;
    emit dataModelUpdated();
}


void
PrimitiveNodeTypeConverter::
build(const QtNodes::NodeDataType& dataType)
{
    _caption = "To " + dataType.name;
    _name = "to_" + dataType.id;
    _outDataType = dataType;
}


PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
toDoubleFactory()
{
    return m_createFactory(DoubleDataType{});
}


PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
toFloatFactory()
{
    return m_createFactory(FloatDataType{});
}


PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
toIntegerFactory()
{
    return m_createFactory(IntegerDataType{});
}


PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
toUnsignedIntegerFactory()
{
    return m_createFactory(UnsignedIntegerDataType{});
}

PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
toBooleanFactory()
{
    return m_createFactory(BooleanDataType{});
}


PrimitiveNodeTypeConverter::Factory
PrimitiveNodeTypeConverter::
m_createFactory(const QtNodes::NodeDataType& dataType)
{
    return [dataType]() -> std::unique_ptr<NodeDataModel> {
        auto model = std::make_unique<PrimitiveNodeTypeConverter>();
        model->build(dataType);
        return std::move(model);
    };
}

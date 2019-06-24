#include "GeometrycFunctionalNodes.hpp"

#include <nodes/Connection>
#include "DataTypeInteractionRules.hpp"
#include "GlobalConstants.hpp"
#include "ShaderNodeDataTypes.hpp"

QJsonObject
NormalizeFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
NormalizeFunctionalNode::
caption() const
{
    return "Normalize";
}


QString
NormalizeFunctionalNode::
name() const
{
    return "Normalize";
}


unsigned int
NormalizeFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
NormalizeFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
NormalizeFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
NormalizeFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
NormalizeFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
LengthFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;

    return obj;
}


QString
LengthFunctionalNode::
caption() const
{
    return "Length";
}


QString
LengthFunctionalNode::
name() const
{
    return "Length";
}


unsigned int
LengthFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
LengthFunctionalNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return FloatDataType{};
    }

    return _type;
}


bool
LengthFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
LengthFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
LengthFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
DistanceFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;

    return obj;
}


QString
DistanceFunctionalNode::
caption() const
{
    return "Distance";
}


QString
DistanceFunctionalNode::
name() const
{
    return "Distance";
}


unsigned int
DistanceFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
DistanceFunctionalNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return FloatDataType{};
    }

    return _type;
}


bool
DistanceFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
DistanceFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
DistanceFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}


QJsonObject
DotFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;

    return obj;
}


QString
DotFunctionalNode::
caption() const
{
    return "Dot";
}


QString
DotFunctionalNode::
name() const
{
    return "Dot";
}


unsigned int
DotFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
DotFunctionalNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return FloatDataType{};
    }

    return _type;
}


bool
DotFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
DotFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
DotFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}


QJsonObject
CrossFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;

    return obj;
}


QString
CrossFunctionalNode::
caption() const
{
    return "Cross";
}


QString
CrossFunctionalNode::
name() const
{
    return "Cross";
}


unsigned int
CrossFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
CrossFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return Vec3DataType{};
}


QJsonObject
ReflectFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
ReflectFunctionalNode::
caption() const
{
    return "Reflect";
}


QString
ReflectFunctionalNode::
name() const
{
    return "Reflect";
}


unsigned
int ReflectFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
ReflectFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
ReflectFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
ReflectFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
ReflectFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}

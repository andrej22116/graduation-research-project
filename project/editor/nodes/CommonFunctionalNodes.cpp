#include "CommonFunctionalNodes.hpp"

#include <nodes/Connection>
#include "DataTypeInteractionRules.hpp"
#include "GlobalConstants.hpp"

QJsonObject
AbsoluteFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["d_t"] = _type.id;

    return obj;
}


QString
AbsoluteFunctionalNode::
caption() const
{
    return "Absolute";
}


QString
AbsoluteFunctionalNode::
name() const
{
    return "Absolute";
}


unsigned int
AbsoluteFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
AbsoluteFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
AbsoluteFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
AbsoluteFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
AbsoluteFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
SignFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
SignFunctionalNode::
caption() const
{
    return "Sign";
}


QString
SignFunctionalNode::
name() const
{
    return "Sign";
}


unsigned int
SignFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
SignFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
SignFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
SignFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
SignFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
FloorFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
FloorFunctionalNode::
caption() const
{
    return "Floor";
}


QString
FloorFunctionalNode::
name() const
{
    return "Floor";
}


unsigned
int FloorFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
FloorFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
FloorFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
FloorFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
FloorFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
CeilingFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
CeilingFunctionalNode::
caption() const
{
    return "Ceiling";
}


QString
CeilingFunctionalNode::
name() const
{
    return "Ceiling";
}


unsigned int
CeilingFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
CeilingFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
CeilingFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
CeilingFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
CeilingFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
FractionalFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
FractionalFunctionalNode::
caption() const
{
    return "Fractional";
}


QString
FractionalFunctionalNode::
name() const
{
    return "Fractional";
}


unsigned int
FractionalFunctionalNode::
nPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
FractionalFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
FractionalFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
FractionalFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    _type = connection.dataType(QtNodes::PortType::Out);
    emit dataModelUpdated();
}


void
FractionalFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    _type = NO_DATA_TYPE;
    emit dataModelUpdated();
}


QJsonObject
ModuloFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
ModuloFunctionalNode::
caption() const
{
    return "Modulo";
}


QString
ModuloFunctionalNode::
name() const
{
    return "Modulo";
}


unsigned int
ModuloFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
ModuloFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
ModuloFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
ModuloFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
ModuloFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}


QJsonObject
MinimumFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
MinimumFunctionalNode::
caption() const
{
    return "Minimum";
}


QString
MinimumFunctionalNode::
name() const
{
    return "Minimum";
}


unsigned
int MinimumFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
MinimumFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
MinimumFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
MinimumFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
MinimumFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}


QJsonObject
MaximumFunctionalNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj[JSON_TYPE] = JSON_TYPE_FUNCTION;
    obj["out_t"] = _type.id;

    return obj;
}


QString
MaximumFunctionalNode::
caption() const
{
    return "Maximum";
}


QString
MaximumFunctionalNode::
name() const
{
    return "Maximum";
}


unsigned
int MaximumFunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
MaximumFunctionalNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _type;
}


bool
MaximumFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& type ) const
{
    return DataTypeInteractionRules::isFloatingType(type);
}


void
MaximumFunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( _connectionsCount == 0 ) {
        _type = connection.dataType(QtNodes::PortType::Out);
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
MaximumFunctionalNode::
inputConnectionDeleted(const QtNodes::Connection&)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}

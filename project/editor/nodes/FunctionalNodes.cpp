#include "FunctionalNodes.hpp"
#include "ShaderNodeDataTypes.hpp"
#include "GlobalConstants.hpp"

#include <nodes/Connection>
#include "DataTypeInteractionRules.hpp"

#include <QDebug>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
AdderFunctionalNode::
name() const
{
    return "Adder";
}


QString
AdderFunctionalNode::
caption() const
{
    return "Adder";
}


QJsonObject
AdderFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["in_1_t"] = _firstPortDataType.id;
    nodeJSON["in_2_t"] = _secondPortDataType.id;
    nodeJSON["out_t"] = _resultDataType.id;

    return nodeJSON;
}


unsigned int
AdderFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
AdderFunctionalNode::
functionalDataType( QtNodes::PortType portType
                  , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return _resultDataType;
    }

    if ( portIndex == 1 ) {
        return _firstPortDataType;
    }
    else if ( portIndex == 2 ) {
        return _secondPortDataType;
    }

    return NO_DATA_TYPE;
}


bool
AdderFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType portType
                            , QtNodes::PortIndex portIndex ) const
{
    return portType == QtNodes::PortType::Out && portIndex == 1;
}


QString
AdderFunctionalNode::
functionalPortCaption( QtNodes::PortType
                     , QtNodes::PortIndex ) const
{
    return "Sum";
}


void
AdderFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex portIndex
                           , const QtNodes::NodeDataType& dataType )
{

    if ( portIndex == 1 ) {
        _firstPortUsed = true;
        _firstPortDataType = dataType;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();
}


void
AdderFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();

}


bool
AdderFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !_firstPortUsed && !_secondPortUsed ) {
        return DataTypeInteractionRules::canBeAdded(nodeDataType);
    }
    else if ( _firstPortUsed ) {
        return DataTypeInteractionRules::canBeAdded( _firstPortDataType
                                                   , nodeDataType );
    }
    else if ( _secondPortUsed ) {
        return DataTypeInteractionRules::canBeAdded( _secondPortDataType
                                                   , nodeDataType );
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
SubtractorFunctionalNode::
name() const
{
    return "Substractor";
}


QString
SubtractorFunctionalNode::
caption() const
{
    return "Substractor";
}


QJsonObject
SubtractorFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["in_1_t"] = _firstPortDataType.id;
    nodeJSON["in_2_t"] = _secondPortDataType.id;
    nodeJSON["out_t"] = _resultDataType.id;

    return nodeJSON;
}


unsigned int
SubtractorFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
SubtractorFunctionalNode::
functionalDataType( QtNodes::PortType portType
                  , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return _resultDataType;
    }

    if ( portIndex == 1 ) {
        return _firstPortDataType;
    }
    else if ( portIndex == 2 ) {
        return _secondPortDataType;
    }

    return NO_DATA_TYPE;
}


bool
SubtractorFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType
                            , QtNodes::PortIndex ) const
{
    return true;
}


QString
SubtractorFunctionalNode::
functionalPortCaption( QtNodes::PortType portType
                     , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) { return "Difference"; }
    return portIndex == 0 ? "Minuend" : "Subtrahend";
}


void
SubtractorFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex portIndex
                           , const QtNodes::NodeDataType& dataType )
{

    if ( portIndex == 1 ) {
        _firstPortUsed = true;
        _firstPortDataType = dataType;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();
}


void
SubtractorFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();
}


bool
SubtractorFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !_firstPortUsed && !_secondPortUsed ) {
        return DataTypeInteractionRules::canBeSubtracted(nodeDataType);
    }
    else if ( _firstPortUsed ) {
        return DataTypeInteractionRules::canBeSubtracted( _firstPortDataType
                                                        , nodeDataType );
    }
    else if ( _secondPortUsed ) {
        return DataTypeInteractionRules::canBeSubtracted( _secondPortDataType
                                                        , nodeDataType );
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
ConditionFunctionalNode::
name() const
{
    return "Condition";
}


QString
ConditionFunctionalNode::
caption() const
{
    return "Condition";
}


QJsonObject
ConditionFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;

    return nodeJSON;
}


unsigned int
ConditionFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 1 : 2;
}


QtNodes::NodeDataType
ConditionFunctionalNode::
functionalDataType( QtNodes::PortType portType
                  , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::In ) {
        return BooleanDataType{};
    }
    else {
        return ActionDataType{};
    }
}


bool
ConditionFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType
                            , QtNodes::PortIndex ) const
{
    return true;
}


QString
ConditionFunctionalNode::
functionalPortCaption( QtNodes::PortType portType
                     , QtNodes::PortIndex portIndex ) const
{
    if ( portType == PortType::In ) {
        return "Condition(bool)";
    }

    return portIndex == 1 ? "True"
                          : "False";
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
RadiansFunctionalNode::
name() const
{
    return "To radians";
}


QString
RadiansFunctionalNode::
caption() const
{
    return "To radians";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
DegreesFunctionalNode::
name() const
{
    return "To degrees";
}


QString
DegreesFunctionalNode::
caption() const
{
    return "To degrees";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

unsigned int
TrigonometryFunctionalNode::
functionalNPorts(QtNodes::PortType) const
{
    return 1;
}


QtNodes::NodeDataType
TrigonometryFunctionalNode::
functionalDataType( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return _dataType;
}


void
TrigonometryFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex
                           , const QtNodes::NodeDataType& dataType )
{
    _dataType = dataType;
    emit dataModelUpdated();
}


void
TrigonometryFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex)
{
    _dataType = NO_DATA_TYPE;
    emit dataModelUpdated();
}


bool
TrigonometryFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType&) const
{
    return true;
}


QJsonObject
TrigonometryFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["out_t"] = _dataType.id;

    return nodeJSON;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
SinFunctionalNode::
name() const
{
    return "Sine";
}


QString
SinFunctionalNode::
caption() const
{
    return "Sine";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
CosFunctionalNode::
name() const
{
    return "Cosine";
}


QString
CosFunctionalNode::
caption() const
{
    return "Cosine";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
TanFunctionalNode::
name() const
{
    return "Tangent";
}


QString
TanFunctionalNode::
caption() const
{
    return "Tangent";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
CtanFunctionalNode::
name() const
{
    return "Cotangent";
}


QString
CtanFunctionalNode::
caption() const
{
    return "Cotangent";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
ArcSinFunctionalNode::
name() const
{
    return "Arc sine";
}


QString
ArcSinFunctionalNode::
caption() const
{
    return "Arc sine";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
ArcCosFunctionalNode::
name() const
{
    return "Arc cosine";
}


QString
ArcCosFunctionalNode::
caption() const
{
    return "Arc cosine";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
ArcTanFunctionalNode::
name() const
{
    return "Arc tangent";
}


QString
ArcTanFunctionalNode::
caption() const
{
    return "Arc tangent";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
PowFunctionalNode::
name() const
{
    return "Power";
}


QString
PowFunctionalNode::
caption() const
{
    return "Power";
}


QJsonObject
PowFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["out_t"] = _type.id;

    return nodeJSON;
}


unsigned int
PowFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
PowFunctionalNode::
functionalDataType( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return _type;
}


bool
PowFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType portType
                            , QtNodes::PortIndex ) const
{
    return portType == QtNodes::PortType::In;
}


QString
PowFunctionalNode::
functionalPortCaption( QtNodes::PortType
                     , QtNodes::PortIndex portIndex ) const
{
    return portIndex == 1 ? "Value" : "Power";
}


void
PowFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex
                           , const QtNodes::NodeDataType& dataType )
{
    if ( _connectionsCount == 0 ) {
        _type = dataType;
        emit dataModelUpdated();
    }
    ++_connectionsCount;
}


void
PowFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex)
{
    --_connectionsCount;
    if ( _connectionsCount == 0 ) {
        _type = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
}


bool
PowFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    return DataTypeInteractionRules::isFloatingType(nodeDataType);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
ExpFunctionalNode::
name() const
{
    return "Exponentiation";
}


QString
ExpFunctionalNode::
caption() const
{
    return "Exponentiation";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
Exp2FunctionalNode::
name() const
{
    return "Exponentiation 2";
}


QString
Exp2FunctionalNode::
caption() const
{
    return "Exponentiation 2";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
LogFunctionalNode::
name() const
{
    return "Logarithm";
}


QString
LogFunctionalNode::
caption() const
{
    return "Logarithm";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
Log2FunctionalNode::
name() const
{
    return "Logarithm base 2";
}


QString
Log2FunctionalNode::
caption() const
{
    return "Logarithm base 2";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
SqrtFunctionalNode::
name() const
{
    return "Sqrt";
}


QString
SqrtFunctionalNode::
caption() const
{
    return "Sqrt";
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
InverseSqrtFunctionalNode::
name() const
{
    return "Inverse sqrt";
}


QString
InverseSqrtFunctionalNode::
caption() const
{
    return "Inverse sqrt";
}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

unsigned int
FunctionalNode::
nPorts(QtNodes::PortType portType) const
{
    return 1 + functionalNPorts(portType);
}


QtNodes::NodeDataType
FunctionalNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) {
        return ActionDataType{};
    }

    return functionalDataType(portType, portIndex);
}


bool
FunctionalNode::
portCaptionVisible( QtNodes::PortType portType
                  , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) {
        return true;
    }

    return functionalPortCaptionVisible(portType, portIndex);
}


QString
FunctionalNode::
portCaption( QtNodes::PortType portType
           , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) {
        return portType == PortType::In
                         ? "Do"
                         : "Next";
    }

    return functionalPortCaption(portType, portIndex);
}


void
FunctionalNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( connection.getPortIndex(PortType::In) == 0 ) {
        return;
    }

    functionalConnectionCreated( connection.getPortIndex(PortType::In)
                               , connection.dataType(PortType::Out) );
}


void
FunctionalNode::
inputConnectionDeleted(const QtNodes::Connection& connection)
{
    if ( connection.getPortIndex(PortType::In) == 0 ) {
        return;
    }

    functionalConnectionDeleted(connection.getPortIndex(PortType::In));
}


bool
FunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType
                            , QtNodes::PortIndex ) const
{
    return false;
}


QString
FunctionalNode::
functionalPortCaption( QtNodes::PortType
                     , QtNodes::PortIndex ) const
{
    return "";
}


NodeDataModel::ConnectionPolicy
FunctionalNode::
portOutConnectionPolicy(QtNodes::PortIndex portIndex) const
{
    return portIndex == 0 ? NodeDataModel::ConnectionPolicy::One
                          : NodeDataModel::ConnectionPolicy::Many;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
BeginNode::
name() const
{
    return "begin";
}


QString
BeginNode::
caption() const
{
    return "Begin node";
}


unsigned int
BeginNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
BeginNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return ActionDataType{};
}


bool
BeginNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
BeginNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "Begin do";
}


NodeDataModel::ConnectionPolicy
BeginNode::
portOutConnectionPolicy(QtNodes::PortIndex) const
{
    return NodeDataModel::ConnectionPolicy::One;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString
MultiplyFunctionalNode::
name() const
{
    return "Multiply";
}


QString
MultiplyFunctionalNode::
caption() const
{
    return "Multiply";
}


QJsonObject
MultiplyFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["in_1_t"] = _firstPortDataType.id;
    nodeJSON["in_2_t"] = _secondPortDataType.id;
    nodeJSON["out_t"] = _resultDataType.id;

    return nodeJSON;
}


unsigned int
MultiplyFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
MultiplyFunctionalNode::
functionalDataType( QtNodes::PortType portType
                  , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return _resultDataType;
    }

    if ( portIndex == 1 ) {
        return _firstPortDataType;
    }
    else if ( portIndex == 2 ) {
        return _secondPortDataType;
    }

    return NO_DATA_TYPE;
}


bool
MultiplyFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType
                            , QtNodes::PortIndex ) const
{
    return true;
}


QString
MultiplyFunctionalNode::
functionalPortCaption( QtNodes::PortType portType
                     , QtNodes::PortIndex portIndex) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return "Product";
    }
    return portIndex == 1 ? "Multiplicands" : "Multiplier";
}


void
MultiplyFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex portIndex
                           , const QtNodes::NodeDataType& dataType )
{

    if ( portIndex == 1 ) {
        _firstPortUsed = true;
        _firstPortDataType = dataType;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();
}


void
MultiplyFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();

}


bool
MultiplyFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !_firstPortUsed && !_secondPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped(nodeDataType);
    }
    else if ( _firstPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped( _firstPortDataType
                                                   , nodeDataType );
    }
    else if ( _secondPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped( _secondPortDataType
                                                      , nodeDataType );
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


QString
DivisionFunctionalNode::
name() const
{
    return "Division";
}


QString
DivisionFunctionalNode::
caption() const
{
    return "Division";
}


QJsonObject
DivisionFunctionalNode::
save() const
{
    QJsonObject nodeJSON = QtNodes::NodeDataModel::save();

    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON["in_1_t"] = _firstPortDataType.id;
    nodeJSON["in_2_t"] = _secondPortDataType.id;
    nodeJSON["out_t"] = _resultDataType.id;

    return nodeJSON;
}


unsigned int
DivisionFunctionalNode::
functionalNPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
DivisionFunctionalNode::
functionalDataType( QtNodes::PortType portType
                  , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return _resultDataType;
    }

    if ( portIndex == 1 ) {
        return _firstPortDataType;
    }
    else if ( portIndex == 2 ) {
        return _secondPortDataType;
    }

    return NO_DATA_TYPE;
}


bool
DivisionFunctionalNode::
functionalPortCaptionVisible( QtNodes::PortType
                            , QtNodes::PortIndex ) const
{
    return true;
}


QString
DivisionFunctionalNode::
functionalPortCaption( QtNodes::PortType portType
                     , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return "Quotient";
    }
    return portIndex == 1 ? "Dividend" : "Divisor";
}


void
DivisionFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex portIndex
                           , const QtNodes::NodeDataType& dataType )
{

    if ( portIndex == 1 ) {
        _firstPortUsed = true;
        _firstPortDataType = dataType;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();
}


void
DivisionFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
    }
    else {
        return;
    }

    _resultDataType = DataTypeInteractionRules::
                      summaryType( _firstPortDataType
                                 , _secondPortDataType );

    emit dataModelUpdated();

}


bool
DivisionFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !_firstPortUsed && !_secondPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped(nodeDataType);
    }
    else if ( _firstPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped( _firstPortDataType
                                                   , nodeDataType );
    }
    else if ( _secondPortUsed ) {
        return DataTypeInteractionRules::canBeMultiped( _secondPortDataType
                                                      , nodeDataType );
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

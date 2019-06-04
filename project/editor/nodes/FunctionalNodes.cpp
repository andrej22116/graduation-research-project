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
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ADDER_FUNCTIONAL_NODE;

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
        return DataTypeInteractionRules::summaryType( _firstPortDataType
                                                             , _secondPortDataType );
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
    return portType == QtNodes::PortType::Out && portIndex == 0;
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
        emit dataModelUpdated();
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
        emit dataModelUpdated();
    }
    else {
        return;
    }
}


void
AdderFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else {
        return;
    }
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
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SUBSTRACTOR_FUNCTIONAL_NODE;

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
        return DataTypeInteractionRules::summaryType( _firstPortDataType
                                                             , _secondPortDataType );
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
        emit dataModelUpdated();
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
        emit dataModelUpdated();
    }
    else {
        return;
    }
}


void
SubtractorFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex portIndex)
{
    if ( portIndex == 1 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else if ( portIndex == 2 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else {
        return;
    }
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
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_CONDITION_FUNCTIONAL_NODE;

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


NodeDataModel::ConnectionPolicy
ConditionFunctionalNode::
portOutConnectionPolicy(QtNodes::PortIndex) const
{
    return NodeDataModel::ConnectionPolicy::One;
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


QJsonObject
RadiansFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_RADIANS_FUNCTIONAL_NODE;

    return nodeJSON;
}


QtNodes::NodeDataType
RadiansFunctionalNode::
functionalDataType( QtNodes::PortType
                  , QtNodes::PortIndex) const
{
    return FloatDataType{};
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


QJsonObject
DegreesFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_DEGREES_FUNCTIONAL_NODE;

    return nodeJSON;
}


QtNodes::NodeDataType
DegreesFunctionalNode::
functionalDataType( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return _dataType;
}


void
DegreesFunctionalNode::
functionalConnectionCreated( QtNodes::PortIndex
                           , const QtNodes::NodeDataType& dataType )
{
    _dataType = dataType;
    emit dataModelUpdated();
}


void
DegreesFunctionalNode::
functionalConnectionDeleted(QtNodes::PortIndex)
{
    _dataType = {};
    emit dataModelUpdated();
}


bool
DegreesFunctionalNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& dataType ) const
{
    return dataType.id != ActionDataType{}.id;
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


QJsonObject
SinFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SIN_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
CosFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_COS_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
TanFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_TAN_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
CtanFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_CTAN_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
ArcSinFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_SIN_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
ArcCosFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_COS_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
ArcTanFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_TAN_FUNCTIONAL_NODE;

    return nodeJSON;
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
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_POWER_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
ExpFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_EXP_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
Exp2FunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_EXP2_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
LogFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_LOG_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
Log2FunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_LOG2_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
SqrtFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SQRT_FUNCTIONAL_NODE;

    return nodeJSON;
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


QJsonObject
InverseSqrtFunctionalNode::
save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ISQRT_FUNCTIONAL_NODE;

    return nodeJSON;
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


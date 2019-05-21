#include "FunctionalNodes.hpp"
#include "ShaderNodeDataTypes.hpp"
#include "GlobalConstants.hpp"

#include <nodes/Connection>

unsigned int FunctionalNode::nPorts(QtNodes::PortType) const
{
    return 1;
}

QtNodes::NodeDataType FunctionalNode::dataType(QtNodes::PortType
                                              , QtNodes::PortIndex ) const
{
    return ActionDataType{};
}

QString FunctionalNode::portCaption( QtNodes::PortType
                                   , QtNodes::PortIndex ) const
{
    return "";
}

bool FunctionalNode::portCaptionVisible( QtNodes::PortType
                                       , QtNodes::PortIndex ) const
{
    return false;
}

NodeDataModel::ConnectionPolicy FunctionalNode::portOutConnectionPolicy(QtNodes::PortIndex portIndex) const
{
    return portIndex == 0 ? NodeDataModel::ConnectionPolicy::One
                          : NodeDataModel::ConnectionPolicy::Many;
}

QString AdderFunctionalNode::name() const
{
    return "Adder";
}

QString AdderFunctionalNode::caption() const
{
    return "Adder";
}

QJsonObject AdderFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ADDER_FUNCTIONAL_NODE;

    return nodeJSON;
}

unsigned int AdderFunctionalNode::nPorts(QtNodes::PortType portType) const
{
    return (portType == QtNodes::PortType::In ? 2 : 1) + 1;
}

QtNodes::NodeDataType AdderFunctionalNode::dataType( QtNodes::PortType
                                                   , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return FloatDataType{};
}

bool AdderFunctionalNode::portCaptionVisible( QtNodes::PortType portType
                                            , QtNodes::PortIndex portIndex ) const
{
    return portType == QtNodes::PortType::Out && portIndex > 0;
}

QString AdderFunctionalNode::portCaption( QtNodes::PortType
                                        , QtNodes::PortIndex ) const
{
    return "Sum";
}

QString SubtractorFunctionalNode::name() const
{
    return "Substractor";
}

QString SubtractorFunctionalNode::caption() const
{
    return "Substractor";
}

QJsonObject SubtractorFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SUBSTRACTOR_FUNCTIONAL_NODE;

    return nodeJSON;
}

unsigned int SubtractorFunctionalNode::nPorts(QtNodes::PortType portType) const
{
    return (portType == QtNodes::PortType::In ? 2 : 1) + 1;
}

QtNodes::NodeDataType SubtractorFunctionalNode::dataType( QtNodes::PortType
                                                        , QtNodes::PortIndex portIndex) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return FloatDataType{};
}

bool SubtractorFunctionalNode::portCaptionVisible( QtNodes::PortType
                                                 , QtNodes::PortIndex portIndex ) const
{
    return portIndex > 0;
}

QString SubtractorFunctionalNode::portCaption( QtNodes::PortType portType
                                             , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) { return "Difference"; }
    return portIndex == 1 ? "Minuend" : "Subtrahend";
}

QString ConditionFunctionalNode::name() const
{
    return "Condition";
}

QString ConditionFunctionalNode::caption() const
{
    return "Condition";
}

QJsonObject ConditionFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_CONDITION_FUNCTIONAL_NODE;

    return nodeJSON;
}

unsigned int ConditionFunctionalNode::nPorts(QtNodes::PortType portType) const
{
    return (portType == QtNodes::PortType::In ? 1 : 2) + 1;
}

QtNodes::NodeDataType ConditionFunctionalNode::dataType( QtNodes::PortType portType
                                                       , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::In ) {
        switch ( portIndex ) {
        case 0: return ActionDataType{};
        case 1: return BooleanDataType{};
        }
    }

    return ActionDataType{};
}

bool ConditionFunctionalNode::portCaptionVisible( QtNodes::PortType portType
                                                , QtNodes::PortIndex portIndex ) const
{
    return portType == QtNodes::PortType::Out && portIndex > 0;
}

QString ConditionFunctionalNode::portCaption( QtNodes::PortType
                                            , QtNodes::PortIndex portIndex ) const
{
    switch ( portIndex ) {
    case 1: return "Then action...";
    case 2: return "Else action...";
    default: return "";
    }
}

NodeDataModel::ConnectionPolicy ConditionFunctionalNode::portOutConnectionPolicy(QtNodes::PortIndex) const
{
    return NodeDataModel::ConnectionPolicy::One;
}

QString RadiansFunctionalNode::name() const
{
    return "To radians";
}

QString RadiansFunctionalNode::caption() const
{
    return "To radians";
}

QJsonObject RadiansFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_RADIANS_FUNCTIONAL_NODE;

    return nodeJSON;
}

QtNodes::NodeDataType RadiansFunctionalNode::dataType( QtNodes::PortType
                                                     , QtNodes::PortIndex portIndex) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return FloatDataType{};
}

QString DegreesFunctionalNode::name() const
{
    return "To degrees";
}

QString DegreesFunctionalNode::caption() const
{
    return "To degrees";
}

QJsonObject DegreesFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_DEGREES_FUNCTIONAL_NODE;

    return nodeJSON;
}

QtNodes::NodeDataType DegreesFunctionalNode::dataType( QtNodes::PortType
                                                     , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return /*FloatDataType*/{_dataType, _dataType};
}

void DegreesFunctionalNode::inputConnectionCreated(const QtNodes::Connection& connection)
{
    if ( connection.getPortIndex(PortType::Out) == 0 ) {
        return;
    }

    auto _inputDataType = connection.dataType(PortType::In).id;
    if ( _inputDataType == "a" ) {
        connection.removeFromNodes();
        return;
    }

    _dataType = _inputDataType;
    emit dataModelUpdated();
}

void DegreesFunctionalNode::inputConnectionDeleted(const QtNodes::Connection& connection)
{
    if ( connection.getPortIndex(PortType::Out) == 0 ) {
        return;
    }
    _dataType = "";
    emit dataModelUpdated();
}

unsigned int TrigonometryFunctionalNode::nPorts(QtNodes::PortType portType) const
{
    return 2;
}

NodeDataModel::ConnectionPolicy
TrigonometryFunctionalNode::portOutConnectionPolicy(QtNodes::PortIndex portIndex) const
{
    return portIndex == 0 ? NodeDataModel::ConnectionPolicy::One
                          : NodeDataModel::ConnectionPolicy::Many;
}

QtNodes::NodeDataType TrigonometryFunctionalNode::dataType( QtNodes::PortType
                                                          , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return FloatDataType{};
}

QString SinFunctionalNode::name() const
{
    return "Sine";
}

QString SinFunctionalNode::caption() const
{
    return "Sine";
}

QJsonObject SinFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SIN_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString CosFunctionalNode::name() const
{
    return "Cosine";
}

QString CosFunctionalNode::caption() const
{
    return "Cosine";
}

QJsonObject CosFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_COS_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString TanFunctionalNode::name() const
{
    return "Tangent";
}

QString TanFunctionalNode::caption() const
{
    return "Tangent";
}

QJsonObject TanFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_TAN_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString CtanFunctionalNode::name() const
{
    return "Cotangent";
}

QString CtanFunctionalNode::caption() const
{
    return "Cotangent";
}

QJsonObject CtanFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_CTAN_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString ArcSinFunctionalNode::name() const
{
    return "Arc sine";
}

QString ArcSinFunctionalNode::caption() const
{
    return "Arc sine";
}

QJsonObject ArcSinFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_SIN_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString ArcCosFunctionalNode::name() const
{
    return "Arc cosine";
}

QString ArcCosFunctionalNode::caption() const
{
    return "Arc cosine";
}

QJsonObject ArcCosFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_COS_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString ArcTanFunctionalNode::name() const
{
    return "Arc tangent";
}

QString ArcTanFunctionalNode::caption() const
{
    return "Arc tangent";
}

QJsonObject ArcTanFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ARC_TAN_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString PowFunctionalNode::name() const
{
    return "Power";
}

QString PowFunctionalNode::caption() const
{
    return "Power";
}

QJsonObject PowFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_POWER_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString ExpFunctionalNode::name() const
{
    return "Exponentiation";
}

QString ExpFunctionalNode::caption() const
{
    return "Exponentiation";
}

QJsonObject ExpFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_EXP_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString Exp2FunctionalNode::name() const
{
    return "Exponentiation 2";
}

QString Exp2FunctionalNode::caption() const
{
    return "Exponentiation 2";
}

QJsonObject Exp2FunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_EXP2_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString LogFunctionalNode::name() const
{
    return "Logarithm";
}

QString LogFunctionalNode::caption() const
{
    return "Logarithm";
}

QJsonObject LogFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_LOG_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString Log2FunctionalNode::name() const
{
    return "Logarithm base 2";
}

QString Log2FunctionalNode::caption() const
{
    return "Logarithm base 2";
}

QJsonObject Log2FunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_LOG2_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString SqrtFunctionalNode::name() const
{
    return "Sqrt";
}

QString SqrtFunctionalNode::caption() const
{
    return "Sqrt";
}

QJsonObject SqrtFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_SQRT_FUNCTIONAL_NODE;

    return nodeJSON;
}

QString InverseSqrtFunctionalNode::name() const
{
    return "Inverse sqrt";
}

QString InverseSqrtFunctionalNode::caption() const
{
    return "Inverse sqrt";
}

QJsonObject InverseSqrtFunctionalNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_FUNCTION;
    nodeJSON[JSON_NAME] = SHORT_NAME_OF_ISQRT_FUNCTIONAL_NODE;

    return nodeJSON;
}

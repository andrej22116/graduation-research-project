#include "FunctionalNodes.hpp"
#include "ShaderNodeDataTypes.hpp"

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

std::string AdderFunctionalNode::whatThis() const
{
    return "+";
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

std::string SubtractorFunctionalNode::whatThis() const
{
    return "-";
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

std::string ConditionFunctionalNode::whatThis() const
{
    return "if";
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

std::string RadiansFunctionalNode::whatThis() const
{
    return "2rad";
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

std::string DegreesFunctionalNode::whatThis() const
{
    return "2deg";
}

QtNodes::NodeDataType DegreesFunctionalNode::dataType( QtNodes::PortType
                                                     , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return FloatDataType{};
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

std::string SinFunctionalNode::whatThis() const
{
    return "sin";
}

QString CosFunctionalNode::name() const
{
    return "Cosine";
}

QString CosFunctionalNode::caption() const
{
    return "Cosine";
}

std::string CosFunctionalNode::whatThis() const
{
    return "cos";
}

QString TanFunctionalNode::name() const
{
    return "Tangent";
}

QString TanFunctionalNode::caption() const
{
    return "Tangent";
}

std::string TanFunctionalNode::whatThis() const
{
    return "tan";
}

QString CtanFunctionalNode::name() const
{
    return "Cotangent";
}

QString CtanFunctionalNode::caption() const
{
    return "Cotangent";
}

std::string CtanFunctionalNode::whatThis() const
{
    return "ctan";
}

QString ArcSinFunctionalNode::name() const
{
    return "Arc sine";
}

QString ArcSinFunctionalNode::caption() const
{
    return "Arc sine";
}

std::string ArcSinFunctionalNode::whatThis() const
{
    return "asin";
}

QString ArcCosFunctionalNode::name() const
{
    return "Arc cosine";
}

QString ArcCosFunctionalNode::caption() const
{
    return "Arc cosine";
}

std::string ArcCosFunctionalNode::whatThis() const
{
    return "acos";
}

QString ArcTanFunctionalNode::name() const
{
    return "Arc tangent";
}

QString ArcTanFunctionalNode::caption() const
{
    return "Arc tangent";
}

std::string ArcTanFunctionalNode::whatThis() const
{
    return "atan";
}

QString PowFunctionalNode::name() const
{
    return "Power";
}

QString PowFunctionalNode::caption() const
{
    return "Power";
}

std::string PowFunctionalNode::whatThis() const
{
    return "pow";
}

QString ExpFunctionalNode::name() const
{
    return "Exponentiation";
}

QString ExpFunctionalNode::caption() const
{
    return "Exponentiation";
}

std::string ExpFunctionalNode::whatThis() const
{
    return "exp";
}

QString Exp2FunctionalNode::name() const
{
    return "Exponentiation 2";
}

QString Exp2FunctionalNode::caption() const
{
    return "Exponentiation 2";
}

std::string Exp2FunctionalNode::whatThis() const
{
    return "exp2";
}

QString LogFunctionalNode::name() const
{
    return "Logarithm";
}

QString LogFunctionalNode::caption() const
{
    return "Logarithm";
}

std::string LogFunctionalNode::whatThis() const
{
    return "log";
}

QString Log2FunctionalNode::name() const
{
    return "Logarithm base 2";
}

QString Log2FunctionalNode::caption() const
{
    return "Logarithm base 2";
}

std::string Log2FunctionalNode::whatThis() const
{
    return "log2";
}

QString SqrtFunctionalNode::name() const
{
    return "Sqrt";
}

QString SqrtFunctionalNode::caption() const
{
    return "Sqrt";
}

std::string SqrtFunctionalNode::whatThis() const
{
    return "sqrt";
}

QString InverseSqrtFunctionalNode::name() const
{
    return "Inverse sqrt";
}

QString InverseSqrtFunctionalNode::caption() const
{
    return "Inverse sqrt";
}

std::string InverseSqrtFunctionalNode::whatThis() const
{
    return "isqrt";
}

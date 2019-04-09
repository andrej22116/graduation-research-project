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
    return IntegerDataType{};
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
    return IntegerDataType{};
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

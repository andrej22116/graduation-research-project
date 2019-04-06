#include "FunctionalNodes.hpp"
#include "ShaderNodeDataTypes.hpp"

unsigned int FunctionalNode::nPorts(QtNodes::PortType portType) const
{
    return 1 + m_nPorts(portType);
}

QtNodes::NodeDataType FunctionalNode::dataType(QtNodes::PortType portType
                                              , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return ActionDataType{}; }
    return m_dataType(portType, portIndex);
}

QString FunctionalNode::portCaption( QtNodes::PortType portType
                                   , QtNodes::PortIndex portIndex ) const
{
    return m_portCaption(portType, portIndex);
}

bool FunctionalNode::portCaptionVisible( QtNodes::PortType portType
                                       , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 ) { return false; }
    return m_portCaptionVisible(portType, portIndex);
}

NodeDataModel::ConnectionPolicy FunctionalNode::portOutConnectionPolicy(QtNodes::PortIndex portIndex) const
{
    if ( portIndex == 0 ) { return NodeDataModel::ConnectionPolicy::One; }
    return m_portOutConnectionPolicy(portIndex);
}

QString FunctionalNode::m_portCaption( QtNodes::PortType
                                     , QtNodes::PortIndex ) const
{
    return "";
}

NodeDataModel::ConnectionPolicy FunctionalNode::m_portOutConnectionPolicy(QtNodes::PortIndex) const
{
    return NodeDataModel::ConnectionPolicy::Many;
}

bool FunctionalNode::m_portCaptionVisible( QtNodes::PortType
                                         , QtNodes::PortIndex ) const
{
    return false;
}

QString AdderFunctionalNode::name() const
{
    return "add";
}

QString AdderFunctionalNode::caption() const
{
    return "Adder";
}

std::string AdderFunctionalNode::whatThis() const
{
    return "+";
}

unsigned int AdderFunctionalNode::m_nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}

QtNodes::NodeDataType AdderFunctionalNode::m_dataType( QtNodes::PortType
                                                     , QtNodes::PortIndex ) const
{
    return IntegerDataType{};
}

bool AdderFunctionalNode::m_portCaptionVisible( QtNodes::PortType portType
                                              , QtNodes::PortIndex ) const
{
    return portType == QtNodes::PortType::Out;
}

QString AdderFunctionalNode::m_portCaption( QtNodes::PortType
                                          , QtNodes::PortIndex ) const
{
    return "Sum";
}

QString SubtractorFunctionalNode::name() const
{
    return "sub";
}

QString SubtractorFunctionalNode::caption() const
{
    return "Substractor";
}

std::string SubtractorFunctionalNode::whatThis() const
{
    return "-";
}

unsigned int SubtractorFunctionalNode::m_nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}

QtNodes::NodeDataType SubtractorFunctionalNode::m_dataType( QtNodes::PortType
                                                          , QtNodes::PortIndex) const
{
    return IntegerDataType{};
}

bool SubtractorFunctionalNode::m_portCaptionVisible( QtNodes::PortType
                                                   , QtNodes::PortIndex ) const
{
    return true;
}

QString SubtractorFunctionalNode::m_portCaption( QtNodes::PortType portType
                                               , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) { return "Difference"; }
    return portIndex == 1 ? "Minuend" : "Subtrahend";
}

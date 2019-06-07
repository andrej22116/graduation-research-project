#include "ConstVariableNode.hpp"

ConstVariableNode::ConstVariableNode( const QString& caption
                                    , const QString& name
                                    , ConstVariableWidget* widget )
{

}


QString
ConstVariableNode::
caption() const
{
}


QString
ConstVariableNode::
name() const
{
}


unsigned int
ConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
}


QtNodes::NodeDataType
ConstVariableNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex portIndex ) const
{
}


QJsonObject
ConstVariableNode::
save() const
{
}


void
ConstVariableNode::
restore(const QJsonObject&)
{
}

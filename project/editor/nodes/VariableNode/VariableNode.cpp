#include "VariableNode.hpp"
#include <QPushButton>
#include <QBoxLayout>
#include "ShaderNodeDataTypes.hpp"
#include "VariableNodePainterDelegate.hpp"

VariableNode::VariableNode( const QString& name
                          , const QtNodes::NodeDataType& dataType)
    : _nodeTypeSelected(false)
    , _dataType(dataType)
    , _name(name)
    , _painterDelegate(new VariableNodePainterDelegate)
{
    _selectorNodeTypeWidget = new QWidget();
    auto layout = new QBoxLayout( QBoxLayout::TopToBottom
                                , _selectorNodeTypeWidget );
    _selectorNodeTypeWidget->setLayout(layout);

    auto buttonSet = new QPushButton("SET", _selectorNodeTypeWidget);
    auto buttonGet = new QPushButton("GET", _selectorNodeTypeWidget);
    layout->addWidget(buttonGet);
    layout->addWidget(buttonSet);

    connect( buttonSet
           , &QPushButton::clicked
           , this
           , [this](){
        _nodeType = QtNodes::PortType::In;
        _nodeTypeSelected = true;
        emit dataModelUpdated();
        delete _selectorNodeTypeWidget;
        _selectorNodeTypeWidget = nullptr;
    });

    connect( buttonGet
           , &QPushButton::clicked
           , this
           , [this](){
        _nodeType = QtNodes::PortType::Out;
        _nodeTypeSelected = true;
        emit dataModelUpdated();
        delete _selectorNodeTypeWidget;
        _selectorNodeTypeWidget = nullptr;
    });
}

VariableNode::
VariableNode( const QString& name
            , const QtNodes::NodeDataType& dataType
            , const QtNodes::PortType type )
    : _nodeTypeSelected(true)
    , _dataType(dataType)
    , _name(name)
    , _nodeType(type)
    , _painterDelegate(new VariableNodePainterDelegate)
{
}

VariableNode::~VariableNode()
{
    delete _painterDelegate;
}


QString
VariableNode::
caption() const
{
    return _name;
}


QString
VariableNode::
name() const
{
    return _name;
}


unsigned int
VariableNode::
nPorts(QtNodes::PortType portType) const
{
    if ( !_nodeTypeSelected ) {
        return 0;
    }

    if ( _nodeType == QtNodes::PortType::In ) {
        return portType == QtNodes::PortType::In ? 2 : 1;
    }
    else {
        return portType == QtNodes::PortType::In ? 0 : 1;
    }
}


QtNodes::NodeDataType
VariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex portIndex ) const
{
    if ( _nodeType == QtNodes::PortType::In ) {
        switch ( portIndex ) {
        case 0: return ActionDataType{};
        case 1: return _dataType;
        default: return NO_DATA_TYPE;
        }
    }
    else {
        return _dataType;
    }
}


QWidget*
VariableNode::
embeddedWidget()
{
    return _selectorNodeTypeWidget;
}


void
VariableNode::
setName(const QString& name)
{
    _name = name;
    emit dataModelUpdated();
}


void
VariableNode::
setDataType(const QtNodes::NodeDataType& dataType)
{
    _dataType = dataType;
    emit dataModelUpdated();
}


QString
VariableNode::
portCaption( QtNodes::PortType portType
           , QtNodes::PortIndex ) const
{
    return portType == QtNodes::PortType::In ? "Do" : "Next";
}


bool
VariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex portIndex ) const
{
    return _nodeType == QtNodes::PortType::In && portIndex == 0;
}


QtNodes::NodeDataModel::ConnectionPolicy
VariableNode::
portOutConnectionPolicy(QtNodes::PortIndex portIndex) const
{
    return _nodeType == QtNodes::PortType::In && portIndex == 0
           ? QtNodes::NodeDataModel::ConnectionPolicy::One
           : QtNodes::NodeDataModel::ConnectionPolicy::Many;
}


QtNodes::NodePainterDelegate*
VariableNode::
painterDelegate() const
{
    return _painterDelegate;
}

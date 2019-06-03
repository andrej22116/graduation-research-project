#include "VariableNode.hpp"
#include <QPushButton>
#include <QBoxLayout>

VariableNode::VariableNode( const QString& name
                          , const QtNodes::NodeDataType& dataType)
    : _nodeTypeSelected(false)
    , _name(name)
    , _dataType(dataType)
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
    return _nodeTypeSelected && portType == _nodeType ? 1 : 0;
}


QtNodes::NodeDataType
VariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return _dataType;
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

#include "VariableNodes.hpp"
#include "ShaderNodeDataTypes.hpp"
#include "GlobalConstants.hpp"
#include "VariableWidgets.hpp"
#include "VariableValueControlsFactory.hpp"

#include <QGridLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

#include <QDebug>

QJsonObject getJsonForTemplate(const QtNodes::NodeDataType& nodeDataType)
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = nodeDataType.name;
    nodeJSON[JSON_TYPE] = JSON_TYPE_VARIABLE;
    nodeJSON[JSON_NAME] = nodeDataType.id;
    nodeJSON[JSON_VARIABLE_TYPE] = JSON_VARIABLE_TYPE_SET;

    return nodeJSON;
}



ConstUserVariableNode::ConstUserVariableNode()
    : _nodeWidget(new QWidget())
{
    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("Type "), 1, 0);

    auto combo = new QComboBox();
    combo->addItems({"Float", "Double", "Int", "Bool"});
    combo->setFixedSize(combo->sizeHint());
    mainLayout->addWidget(combo, 1, 1);

    auto controlsWidget= new QStackedWidget;
    mainLayout->addWidget(controlsWidget, 2, 0, 1, 2);

    controlsWidget->addWidget(VariableValueControlsFactory::makeWidget("float", _nodeWidget));
    controlsWidget->addWidget(VariableValueControlsFactory::makeWidget("double", _nodeWidget));
    controlsWidget->addWidget(VariableValueControlsFactory::makeWidget("int", _nodeWidget));
    controlsWidget->addWidget(VariableValueControlsFactory::makeWidget("bool", _nodeWidget));

    connect( combo
           , static_cast<void (QComboBox::*)(int)>(&QComboBox::activated)
           , this
           , [=](int index) {
                _dataType = combo->itemText(index).toLower();
                controlsWidget->setCurrentIndex(index);

                controlsWidget->setFixedSize(controlsWidget->widget(index)->sizeHint());
                _nodeWidget->setFixedSize(_nodeWidget->sizeHint());

                emit dataModelUpdated();
           } );

    _nodeWidget->setLayout(mainLayout);
    _nodeWidget->setMaximumSize(_nodeWidget->sizeHint());

    _nodeWidget->setObjectName("node-widget");
    _nodeWidget->setStyleSheet(
                "#node-widget{ background-color: transparent; } "
                "QLabel{ color: white; }");

    _dataType = combo->itemText(0).toLower();
}

ConstUserVariableNode::~ConstUserVariableNode()
{
}

QWidget* ConstUserVariableNode::embeddedWidget()
{
    return _nodeWidget;
}

QString ConstUserVariableNode::name() const
{
    return "const";
}

QString ConstUserVariableNode::caption() const
{
    return "Constant";
}

unsigned int ConstUserVariableNode::nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}

QtNodes::NodeDataType ConstUserVariableNode::dataType( QtNodes::PortType
                                                       , QtNodes::PortIndex ) const
{
    return { _dataType.toLower(), _dataType };
}

QJsonObject ConstUserVariableNode::save() const
{
    return {};
}


/*
QString TimeVariableNode::name() const
{
    return "Time";
}

QString TimeVariableNode::caption() const
{
    return "Time";
}

unsigned int TimeVariableNode::nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}

QtNodes::NodeDataType TimeVariableNode::dataType( QtNodes::PortType
                                                , QtNodes::PortIndex) const
{
    return UnsignedIntegerDataType{};
}

QJsonObject TimeVariableNode::save() const
{
    QJsonObject nodeJSON;

    nodeJSON[JSON_NODE] = name();
    nodeJSON[JSON_TYPE] = JSON_TYPE_VARIABLE;
    nodeJSON[JSON_NAME] = name();

    return nodeJSON;
}*/

UserVariableNode::UserVariableNode()
{
    auto widget = embeddedWidget();
    auto layout = dynamic_cast<QGridLayout*>(widget->layout());
    auto lineEdit = new QLineEdit(widget);
    auto label = new QLabel("Name ", widget);

    connect(lineEdit, &QLineEdit::textChanged, this, [this](const QString& newVal){
        this->_varName = newVal;
    });

    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 0, 1);
}

QString UserVariableNode::name() const
{
    return "vardef";
}

QString UserVariableNode::caption() const
{
    return "Variable";
}

QJsonObject UserVariableNode::save() const
{
    return ConstUserVariableNode::save();
}

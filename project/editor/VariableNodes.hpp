#ifndef VARIABLENODES_HPP
#define VARIABLENODES_HPP

#include <nodes/NodeDataModel>
#include "ShaderNodeDataTypes.hpp"

using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;

class VariableWidget;


class UserVariableNode : public NodeDataModel {
    Q_OBJECT

public:
    /// @warning This is dummy!
    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}
    /// @warning This is dummy!
    std::shared_ptr<NodeData> outData(PortIndex) override { return nullptr; }
};


/// Used for define user variables
class ConstUserVariableNode : public UserVariableNode {
    Q_OBJECT

public:
    ConstUserVariableNode();
    ~ConstUserVariableNode() override;

    QWidget* embeddedWidget() override;

    QString name() const override;

    QString caption() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType /*portType*/
                         , PortIndex portIndex ) const override;

    QJsonObject save() const override;

    //bool resizable() const override { return true; }

private:
    QString _dataType;
    QWidget* _nodeWidget;
    VariableWidget* _variableWidget = nullptr;
};

/*
/// Used for define user variables
class UserVariableDefinerNode : public ConstUserVariableNode {
    Q_OBJECT

public:
    QWidget* embeddedWidget() override;

    QString name() const override;

    QString caption() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType /*portType*
                         , PortIndex portIndex ) const override;

    QJsonObject save() const override;

private slots:
    void onActivated(const QString& text);

private:
    QString _dataType;
};*/


class TimeVariableNode : public UserVariableNode {
    QString name() const override;

    QString caption() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    QJsonObject save() const override;
};

#endif // VARIABLENODES_HPP

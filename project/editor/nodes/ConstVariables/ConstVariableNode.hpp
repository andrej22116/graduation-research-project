#ifndef CONSTVARIABLENODE_HPP
#define CONSTVARIABLENODE_HPP

#include <nodes/NodeDataModel>

class ConstVariableWidget;

class ConstVariableNode : public QtNodes::NodeDataModel
{
public:
    ConstVariableNode( const QString& caption
                     , const QString& name
                     , ConstVariableWidget* widget );

    // NodeDataModel interface
public:
    QString caption() const override;

    QString name() const override;

    unsigned int nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType dataType( QtNodes::PortType portType
                                  , QtNodes::PortIndex portIndex ) const override;

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

private:
    QString _caption;
    QString _name;
    ConstVariableWidget* widget;
};

#endif // CONSTVARIABLENODE_HPP

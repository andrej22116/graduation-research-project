#ifndef VARIABLENODE_HPP
#define VARIABLENODE_HPP

#include <nodes/NodeDataModel>

class VariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    VariableNode( const QString& name
                , const QtNodes::NodeDataType& dataType );

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    void
    setInData( std::shared_ptr<QtNodes::NodeData> nodeData
             , QtNodes::PortIndex port ) override {}

    std::shared_ptr<QtNodes::NodeData>
    outData(QtNodes::PortIndex port) override { return nullptr; }

    QWidget*
    embeddedWidget() override;

    QString
    portCaption( QtNodes::PortType
               , QtNodes::PortIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType
                      , QtNodes::PortIndex ) const override;

public:
    void
    setName(const QString& name);

    void
    setDataType(const QtNodes::NodeDataType& dataType);

private:
    bool _nodeTypeSelected;
    QtNodes::NodeDataType _dataType;
    QString _name;
    /// out - set, in - get;
    QtNodes::PortType _nodeType;
    QWidget* _selectorNodeTypeWidget;
};

#endif // VARIABLENODE_HPP

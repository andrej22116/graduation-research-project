#ifndef VARIABLENODE_HPP
#define VARIABLENODE_HPP

#include <nodes/NodeDataModel>

class VariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    VariableNode();

    VariableNode( const QString& name
                , const QtNodes::NodeDataType& dataType );

    VariableNode( const QString& name
                , const QtNodes::NodeDataType& dataType
                , const QtNodes::PortType type);

    ~VariableNode() override;

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

    ConnectionPolicy
    portOutConnectionPolicy(QtNodes::PortIndex) const override;

    QtNodes::NodePainterDelegate*
    painterDelegate() const override;

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

public:
    void
    setVariableName(const QString& name);

    QString
    variableName() const;

    void
    setDataType(const QtNodes::NodeDataType& dataType);

    QtNodes::NodeDataType
    dataType() const;

private:
    void
    createSelectorWidget();

private:
    bool _nodeTypeSelected;
    QtNodes::NodeDataType _dataType;
    QString _name;
    /// in - set, out - get;
    QtNodes::PortType _nodeType;
    QWidget* _selectorNodeTypeWidget;    

    QtNodes::NodePainterDelegate* _painterDelegate;
};

#endif // VARIABLENODE_HPP

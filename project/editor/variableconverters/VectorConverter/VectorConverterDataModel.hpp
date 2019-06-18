#ifndef VECTORCONVERTERDATAMODEL_HPP
#define VECTORCONVERTERDATAMODEL_HPP

#include <nodes/NodeDataModel>
#include <functional>
#include <memory>

using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::Connection;

class VectorConverterWidget;

class VectorConverterDataModel : public NodeDataModel
{
public:
    VectorConverterDataModel() = default;
    ~VectorConverterDataModel() override {}

    QString
    name() const override;

    QString
    caption() const override;

    unsigned int
    nPorts( PortType portType ) const override;

    NodeDataType
    dataType( PortType portType
            , PortIndex portIndex ) const override;

    bool
    portCaptionVisible( PortType portType
                      , PortIndex portIndex ) const override;

    QString
    portCaption( PortType portType
               , PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

    QJsonObject
    save() const override;

    void
    restore(const QJsonObject& object) override;

    void
    inputConnectionCreated(const Connection& connection) override;

    void
    inputConnectionDeleted(const Connection& connection) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;


    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    Vector2Factory();

    static Factory
    Vector3Factory();

    static Factory
    Vector4Factory();

private:
    void
    build(uchar vectorSize);

    static Factory
    s_vectorFactory(uchar vectorSize);

private:
    uchar _vectorSize;
    QString _name;
    QString _caption;
    VectorConverterWidget* _converter;
    NodeDataType _dataType;
    NodeDataType _inputVectorType;
};

#endif // VECTORCONVERTERDATAMODEL_HPP

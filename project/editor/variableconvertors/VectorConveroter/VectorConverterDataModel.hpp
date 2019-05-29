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


    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    Vector2Factory();

    static Factory
    Vector3Factory();

    static Factory
    Vector4Factory();


    /// @warning This is dummy!
    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}
    /// @warning This is dummy!
    std::shared_ptr<NodeData> outData(PortIndex) override { return nullptr; }

private:
    void
    build(uchar vectorSize);

    static Factory
    s_vectorFactory(uchar vectorSize);

private:
    uchar _vectorSize;
    QString _name;
    VectorConverterWidget* _converter;
    NodeDataType _dataType;
};

#endif // VECTORCONVERTERDATAMODEL_HPP

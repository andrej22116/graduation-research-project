#ifndef BASETYPECONVERTERS_HPP
#define BASETYPECONVERTERS_HPP

#include <nodes/NodeDataModel>
#include <functional>

#include <QSet>

class PrimitiveNodeTypeConverter : public QtNodes::NodeDataModel
{
public:
    PrimitiveNodeTypeConverter() = default;

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

    bool
    acceptDataType( QtNodes::PortIndex portIndex
                  , const QtNodes::NodeDataType& nodeDataType ) const override;

    // Serializable interface
public:
    QJsonObject
    save() const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    void
    build(const QtNodes::NodeDataType& dataType);

public:
    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    toDoubleFactory();

    static Factory
    toFloatFactory();

    static Factory
    toIntegerFactory();

    static Factory
    toUnsignedIntegerFactory();

    static Factory
    toBooleanFactory();

private:
    static Factory
    m_createFactory(const QtNodes::NodeDataType& dataType);

private:
    QString _caption;
    QString _name;
    QtNodes::NodeDataType _inDataType;
    QtNodes::NodeDataType _outDataType;

private:
    static QSet<QString> _supportedTypes;
};

#endif // BASETYPECONVERTERS_HPP

#ifndef GEOMETRYCFUNCTIONALNODES_HPP
#define GEOMETRYCFUNCTIONALNODES_HPP

#include <nodes/NodeDataModel>

class NormalizeFunctionalNode : public QtNodes::NodeDataModel
{
public:
    NormalizeFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
    acceptDataType( QtNodes::PortIndex
                  , const QtNodes::NodeDataType& ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    QtNodes::NodeDataType _type;
};


class LengthFunctionalNode : public QtNodes::NodeDataModel
{
public:
    LengthFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
    acceptDataType( QtNodes::PortIndex
                  , const QtNodes::NodeDataType& ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    QtNodes::NodeDataType _type;
};


class DistanceFunctionalNode : public QtNodes::NodeDataModel
{
public:
    DistanceFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
    acceptDataType( QtNodes::PortIndex
                  , const QtNodes::NodeDataType& ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    QtNodes::NodeDataType _type;
    int _connectionsCount = 0;
};


class DotFunctionalNode : public QtNodes::NodeDataModel
{
public:
    DotFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
    acceptDataType( QtNodes::PortIndex
                  , const QtNodes::NodeDataType& ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    QtNodes::NodeDataType _type;
    int _connectionsCount = 0;
};


class CrossFunctionalNode : public QtNodes::NodeDataModel
{
public:
    CrossFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
};


class ReflectFunctionalNode : public QtNodes::NodeDataModel
{
public:
    ReflectFunctionalNode() = default;

    // Serializable interface
public:
    QJsonObject save() const override;

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
    acceptDataType( QtNodes::PortIndex
                  , const QtNodes::NodeDataType& ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

private:
    QtNodes::NodeDataType _type;
    int _connectionsCount = 0;
};

#endif // GEOMETRYCFUNCTIONALNODES_HPP

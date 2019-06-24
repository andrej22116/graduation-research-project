#ifndef COMMONFUNCTIONALNODES_HPP
#define COMMONFUNCTIONALNODES_HPP

#include <nodes/NodeDataModel>

class AbsoluteFunctionalNode : public QtNodes::NodeDataModel
{
public:
    AbsoluteFunctionalNode() = default;

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


class SignFunctionalNode : public QtNodes::NodeDataModel
{
public:
    SignFunctionalNode() = default;

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


class FloorFunctionalNode : public QtNodes::NodeDataModel
{
public:
    FloorFunctionalNode() = default;

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


class CeilingFunctionalNode : public QtNodes::NodeDataModel
{
public:
    CeilingFunctionalNode() = default;

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


class FractionalFunctionalNode : public QtNodes::NodeDataModel
{
public:
    FractionalFunctionalNode() = default;

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


class ModuloFunctionalNode : public QtNodes::NodeDataModel
{
public:
    ModuloFunctionalNode() = default;

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


class MinimumFunctionalNode : public QtNodes::NodeDataModel
{
public:
    MinimumFunctionalNode() = default;

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


class MaximumFunctionalNode : public QtNodes::NodeDataModel
{
public:
    MaximumFunctionalNode() = default;

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

#endif // COMMONFUNCTIONALNODES_HPP

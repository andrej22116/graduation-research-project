#ifndef LOGICKALNODES_HPP
#define LOGICKALNODES_HPP

#include <nodes/NodeDataModel>
#include <functional>
#include <memory>

using QtNodes::NodeDataType;

class LogickalBaseNode : public QtNodes::NodeDataModel {
public:
    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

public slots:
    void
    inputConnectionCreated(const QtNodes::Connection&) override;

    void
    inputConnectionDeleted(const QtNodes::Connection&) override;

protected:
    bool
    firstPortUsed() const;

    const NodeDataType&
    firstPortDataType() const;

    bool
    secondPortUsed() const;

    const NodeDataType&
    secondPortDataType() const;

private:
    NodeDataType _firstPortDataType = NO_DATA_TYPE;
    NodeDataType _secondPortDataType = NO_DATA_TYPE;
    bool _firstPortUsed = false;
    bool _secondPortUsed = false;
};


class LogickalCompareNode : public LogickalBaseNode
{
public:
    LogickalCompareNode( const QString& caption
                       , const QString& name );

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    name() const override;

    bool
    acceptDataType( QtNodes::PortIndex portIndex
                  , const QtNodes::NodeDataType& dataType ) const override;

public:
    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    lessFactory();

    static Factory
    greaterFactory();

    static Factory
    lessOrEqualFactory();

    static Factory
    greaterOrEqualFactory();

private:
    static Factory
    m_factory( const QString& caption
             , const QString& name );

private:
    QString _caption;
    QString _name;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LogickalEqualsNode : public LogickalBaseNode
{
public:
    LogickalEqualsNode( const QString& caption
                      , const QString& name );

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    name() const override;

    bool
    acceptDataType( QtNodes::PortIndex portIndex
                  , const QtNodes::NodeDataType& dataType) const override;

public:
    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    equalityFactory();

    static Factory
    notEqualityFactory();

private:
    static Factory
    m_factory( const QString& caption
             , const QString& name );

private:
    QString _caption;
    QString _name;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LogickalBooleanNode : public QtNodes::NodeDataModel
{
public:
    LogickalBooleanNode( const QString& caption
                       , const QString& name );

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

public:
    using Factory = std::function<std::unique_ptr<NodeDataModel>()>;

    static Factory
    logicalAndFactory();

    static Factory
    logicalOrFactory();

private:
    static Factory
    m_factory( const QString& caption
             , const QString& name );

private:
    QString _caption;
    QString _name;
};


#endif // LOGICKALNODES_HPP

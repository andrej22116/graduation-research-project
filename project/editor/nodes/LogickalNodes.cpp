#include "LogickalNodes.hpp"
#include "ShaderNodeDataTypes.hpp"
#include <nodes/Connection>
#include "DataTypeInteractionRules.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

unsigned int
LogickalBaseNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
LogickalBaseNode::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex portIndex ) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return BooleanDataType{};
    }

    switch ( portIndex ) {
    case 0: return _firstPortDataType;
    case 1: return _secondPortDataType;
    default: return NO_DATA_TYPE;
    }
}


void
LogickalBaseNode::
inputConnectionCreated(const QtNodes::Connection& connection)
{
    auto dataType = connection.dataType(QtNodes::PortType::Out);
    auto portIndex = connection.getPortIndex(QtNodes::PortType::In);

    if ( portIndex == 0 ) {
        _firstPortUsed = true;
        _firstPortDataType = dataType;
        emit dataModelUpdated();
    }
    else if ( portIndex == 1 ) {
        _secondPortUsed = true;
        _secondPortDataType = dataType;
        emit dataModelUpdated();
    }
    else {
        return;
    }
}


void
LogickalBaseNode::
inputConnectionDeleted(const QtNodes::Connection& connection)
{
    auto portIndex = connection.getPortIndex(QtNodes::PortType::In);

    if ( portIndex == 0 ) {
        _firstPortUsed = false;
        _firstPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else if ( portIndex == 1 ) {
        _secondPortUsed = false;
        _secondPortDataType = NO_DATA_TYPE;
        emit dataModelUpdated();
    }
    else {
        return;
    }
}


bool
LogickalBaseNode::
firstPortUsed() const
{
    return _firstPortUsed;
}


const QtNodes::NodeDataType&
LogickalBaseNode::
firstPortDataType() const
{
    return _firstPortDataType;
}


bool
LogickalBaseNode::
secondPortUsed() const
{
    return _secondPortUsed;
}


const QtNodes::NodeDataType&
LogickalBaseNode::
secondPortDataType() const
{
    return _secondPortDataType;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LogickalCompareNode::
LogickalCompareNode( const QString& caption
                   , const QString& name )
    : _caption(caption)
    , _name(name)
{
}


QString
LogickalCompareNode::
caption() const
{
    return _caption;
}


QString
LogickalCompareNode::
name() const
{
    return _name;
}


bool
LogickalCompareNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !firstPortUsed() && !secondPortUsed() ) {
        return DataTypeInteractionRules::canBeCompared(nodeDataType);
    }
    else if ( firstPortUsed() ) {
        return DataTypeInteractionRules::canBeCompared( firstPortDataType()
                                                      , nodeDataType );
    }
    else if ( secondPortUsed() ) {
        return DataTypeInteractionRules::canBeCompared( secondPortDataType()
                                                      , nodeDataType );
    }

    return false;
}


LogickalCompareNode::Factory
LogickalCompareNode::
lessFactory()
{
    return m_factory("<", "less");
}


LogickalCompareNode::Factory
LogickalCompareNode::
greaterFactory()
{
    return m_factory(">", "greater");
}


LogickalCompareNode::Factory
LogickalCompareNode::
lessOrEqualFactory()
{
    return m_factory("<=", "lessOrEqual");
}



LogickalCompareNode::Factory
LogickalCompareNode::
greaterOrEqualFactory()
{
    return m_factory(">=", "greaterOrEqual");
}


LogickalCompareNode::Factory
LogickalCompareNode::
m_factory( const QString& caption
         , const QString& name )
{
    return [caption, name]() -> std::unique_ptr<NodeDataModel> {
        return std::make_unique<LogickalCompareNode>(caption, name);
    };
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LogickalEqualsNode::
LogickalEqualsNode( const QString& caption
                  , const QString& name )
    : _caption(caption)
    , _name(name)
{
}


QString
LogickalEqualsNode::
caption() const
{
    return _caption;
}


QString
LogickalEqualsNode::
name() const
{
    return _name;
}


bool
LogickalEqualsNode::
acceptDataType( QtNodes::PortIndex
              , const QtNodes::NodeDataType& nodeDataType ) const
{
    if ( !firstPortUsed() && !secondPortUsed() ) {
        return DataTypeInteractionRules::canBeEqual(nodeDataType);
    }
    else if ( firstPortUsed() ) {
        return DataTypeInteractionRules::canBeEqual( firstPortDataType()
                                                   , nodeDataType );
    }
    else if ( secondPortUsed() ) {
        return DataTypeInteractionRules::canBeEqual( secondPortDataType()
                                                   , nodeDataType );
    }

    return false;
}


LogickalEqualsNode::Factory
LogickalEqualsNode::
equalityFactory()
{
    return m_factory("Equal", "equal");
}


LogickalEqualsNode::Factory
LogickalEqualsNode::
notEqualityFactory()
{
    return m_factory("Not Equal", "notEqual");
}


LogickalEqualsNode::Factory
LogickalEqualsNode::
m_factory( const QString& caption
         , const QString& name )
{
    return [caption, name]() -> std::unique_ptr<NodeDataModel> {
        return std::make_unique<LogickalEqualsNode>(caption, name);
    };
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LogickalBooleanNode::
LogickalBooleanNode( const QString& caption
                   , const QString& name )
    : _caption(caption)
    , _name(name)
{
}


QString
LogickalBooleanNode::
caption() const
{
    return _caption;
}


QString
LogickalBooleanNode::
name() const
{
    return _name;
}


unsigned int
LogickalBooleanNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}


QtNodes::NodeDataType
LogickalBooleanNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return BooleanDataType{};
}


LogickalBooleanNode::Factory
LogickalBooleanNode::
logicalAndFactory()
{
    return m_factory("AND", "and");
}


LogickalBooleanNode::Factory
LogickalBooleanNode::
logicalOrFactory()
{
    return m_factory("OR", "or");
}


LogickalBooleanNode::Factory
LogickalBooleanNode::
m_factory( const QString& caption
         , const QString& name )
{
    return [caption, name]() -> std::unique_ptr<NodeDataModel> {
        return std::make_unique<LogickalBooleanNode>(caption, name);
    };
}

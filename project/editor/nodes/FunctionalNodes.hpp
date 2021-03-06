#ifndef FUNCTIONALNODES_HPP
#define FUNCTIONALNODES_HPP

#include <nodes/NodeDataModel>

using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::Connection;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BeginNode : public NodeDataModel {
public:
    QString
    name() const override;

    QString
    caption() const override;

    unsigned int
    nPorts( PortType portType ) const override final;

    NodeDataType
    dataType( PortType portType
            , PortIndex portIndex ) const override final;

    bool
    portCaptionVisible( PortType portType
                      , PortIndex portIndex ) const override final;

    QString
    portCaption( PortType portType
               , PortIndex portIndex ) const override final;

    ConnectionPolicy
    portOutConnectionPolicy(QtNodes::PortIndex) const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class FunctionalNode : public NodeDataModel {
public:
    unsigned int
    nPorts( PortType portType ) const override final;

    NodeDataType
    dataType( PortType portType
            , PortIndex portIndex ) const override final;

    bool
    portCaptionVisible( PortType portType
                      , PortIndex portIndex ) const override final;

    QString
    portCaption( PortType portType
               , PortIndex portIndex ) const override final;

    void
    inputConnectionCreated(const Connection& connection) override final;

    void
    inputConnectionDeleted(const Connection& connection) override final;

    ConnectionPolicy
    portOutConnectionPolicy(QtNodes::PortIndex) const override;

public:
    virtual unsigned int
    functionalNPorts( PortType portType ) const = 0;

    virtual NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const = 0;

    virtual bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const;

    virtual QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const;

    virtual void
    functionalConnectionCreated( PortIndex /*portIndex*/
                               , const NodeDataType& /*dataType*/ ){}

    virtual void
    functionalConnectionDeleted( PortIndex /*portIndex*/ ){}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class AdderFunctionalNode : public FunctionalNode {
public:
    AdderFunctionalNode(){}
    ~AdderFunctionalNode() override {}

    /**
     * @brief Name
     * @return Model name
     */
    QString
    name() const override;

    /**
     * @brief caption
     * @return Node title
     */
    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

private:
    NodeDataType _firstPortDataType = NO_DATA_TYPE;
    NodeDataType _secondPortDataType = NO_DATA_TYPE;
    NodeDataType _resultDataType = NO_DATA_TYPE;
    bool _firstPortUsed = false;
    bool _secondPortUsed = false;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SubtractorFunctionalNode : public FunctionalNode {
public:
    SubtractorFunctionalNode(){}
    ~SubtractorFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

private:
    NodeDataType _firstPortDataType = NO_DATA_TYPE;
    NodeDataType _secondPortDataType = NO_DATA_TYPE;
    NodeDataType _resultDataType = NO_DATA_TYPE;
    bool _firstPortUsed = false;
    bool _secondPortUsed = false;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MultiplyFunctionalNode : public FunctionalNode {
public:
    MultiplyFunctionalNode(){}
    ~MultiplyFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

private:
    NodeDataType _firstPortDataType = NO_DATA_TYPE;
    NodeDataType _secondPortDataType = NO_DATA_TYPE;
    NodeDataType _resultDataType = NO_DATA_TYPE;
    bool _firstPortUsed = false;
    bool _secondPortUsed = false;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DivisionFunctionalNode : public FunctionalNode {
public:
    DivisionFunctionalNode(){}
    ~DivisionFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

private:
    NodeDataType _firstPortDataType = NO_DATA_TYPE;
    NodeDataType _secondPortDataType = NO_DATA_TYPE;
    NodeDataType _resultDataType = NO_DATA_TYPE;
    bool _firstPortUsed = false;
    bool _secondPortUsed = false;
};


class PowFunctionalNode : public FunctionalNode {
public:
    PowFunctionalNode() = default;
    ~PowFunctionalNode() override {}

    /**
     * @brief Name
     * @return Model name
     */
    QString
    name() const override;

    /**
     * @brief caption
     * @return Node title
     */
    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

private:
    NodeDataType _type;
    int _connectionsCount;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ConditionFunctionalNode : public FunctionalNode {
public:
    ConditionFunctionalNode(){}
    ~ConditionFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;

    QJsonObject
    save() const override;

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    bool
    functionalPortCaptionVisible( PortType portType
                                , PortIndex portIndex ) const override;

    QString
    functionalPortCaption( PortType portType
                         , PortIndex portIndex ) const override;

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// \brief Trigonometry functions
///

class TrigonometryFunctionalNode : public FunctionalNode {
public:
    TrigonometryFunctionalNode(){}
    ~TrigonometryFunctionalNode() override {}

    unsigned int
    functionalNPorts( PortType portType ) const override;

    NodeDataType
    functionalDataType( PortType portType
                      , PortIndex portIndex ) const override;

    void
    functionalConnectionCreated( PortIndex portIndex
                               , const NodeDataType& dataType ) override;

    void
    functionalConnectionDeleted(PortIndex portIndex) override;

    bool
    acceptDataType( PortIndex portIndex
                  , const NodeDataType& nodeDataType ) const override;

    QJsonObject
    save() const override;

private:
    NodeDataType _dataType = NO_DATA_TYPE;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RadiansFunctionalNode : public TrigonometryFunctionalNode {
public:
    RadiansFunctionalNode(){}
    ~RadiansFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DegreesFunctionalNode : public TrigonometryFunctionalNode {
public:
    DegreesFunctionalNode(){}
    ~DegreesFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;

private:
    NodeDataType _dataType;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SinFunctionalNode : public TrigonometryFunctionalNode {
public:
    SinFunctionalNode(){}
    ~SinFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class CosFunctionalNode : public TrigonometryFunctionalNode {
public:
    CosFunctionalNode(){}
    ~CosFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TanFunctionalNode : public TrigonometryFunctionalNode {
public:
    TanFunctionalNode(){}
    ~TanFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class CtanFunctionalNode : public TrigonometryFunctionalNode {
public:
    CtanFunctionalNode(){}
    ~CtanFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ArcSinFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcSinFunctionalNode(){}
    ~ArcSinFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ArcCosFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcCosFunctionalNode(){}
    ~ArcCosFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ArcTanFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcTanFunctionalNode(){}
    ~ArcTanFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// Exponential
///

class ExpFunctionalNode : public TrigonometryFunctionalNode {
public:
    ExpFunctionalNode(){}
    ~ExpFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Exp2FunctionalNode : public TrigonometryFunctionalNode {
public:
    Exp2FunctionalNode(){}
    ~Exp2FunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LogFunctionalNode : public TrigonometryFunctionalNode {
public:
    LogFunctionalNode(){}
    ~LogFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Log2FunctionalNode : public TrigonometryFunctionalNode {
public:
    Log2FunctionalNode(){}
    ~Log2FunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/// todo: replace float to universal decimal type
class SqrtFunctionalNode : public TrigonometryFunctionalNode {
public:
    SqrtFunctionalNode(){}
    ~SqrtFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/// todo: replace float to universal decimal type
class InverseSqrtFunctionalNode : public TrigonometryFunctionalNode {
public:
    InverseSqrtFunctionalNode(){}
    ~InverseSqrtFunctionalNode() override {}

    QString
    name() const override;

    QString
    caption() const override;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


#endif // FUNCTIONALNODES_HPP

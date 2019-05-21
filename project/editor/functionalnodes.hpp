#ifndef FUNCTIONALNODES_HPP
#define FUNCTIONALNODES_HPP

#include <nodes/NodeDataModel>

using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::Connection;

class FunctionalNode : public NodeDataModel {
public:
    FunctionalNode() {}
    ~FunctionalNode() override {}

    /**
     * @brief nPorts
     * @param portType
     * @return ports amount
     *
     * Node have one input port, one output port
     */
    unsigned int nPorts( PortType portType ) const override;

    /**
     * @brief dataType
     * @param portType
     * @param portIndex
     * @return Data type for port
     *
     * In/Out types: double
     */
    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    /**
     * @brief portCaption
     * @param portType
     * @param portIndex
     * @return port name
     */
    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override;

    /**
     * @brief portCaptionVisible
     * @return only true!
     */
    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex) const override;

    /**
     * @brief portOutConnectionPolicy
     * @param portIndex
     * @return
     */
    ConnectionPolicy portOutConnectionPolicy(PortIndex portIndex) const override;

    ////////////////////////////////////////////////////////////////
    /// @warning This is dummy!
    void setInData( std::shared_ptr<NodeData> nodeData
                  , PortIndex port) override {}
    ///
    /// @warning This is dummy!
    std::shared_ptr<NodeData> outData(PortIndex port) override { return nullptr; }
    ////////////////////////////////////////////////////////////////
};


class AdderFunctionalNode : public FunctionalNode {
public:
    AdderFunctionalNode(){}
    ~AdderFunctionalNode() override {}

    /**
     * @brief Name
     * @return Model name
     */
    QString name() const override;

    /**
     * @brief caption
     * @return Node title
     */
    QString caption() const override;

    QJsonObject save() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex ) const override;

    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override;
};

class SubtractorFunctionalNode : public FunctionalNode {
public:
    SubtractorFunctionalNode(){}
    ~SubtractorFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex ) const override;

    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override;
};

class ConditionFunctionalNode : public FunctionalNode {
public:
    ConditionFunctionalNode(){}
    ~ConditionFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex ) const override;

    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override;

    ConnectionPolicy portOutConnectionPolicy(PortIndex portIndex) const override;
};

///
/// \brief Trigonometry functions
///

class TrigonometryFunctionalNode : public FunctionalNode {
public:
    TrigonometryFunctionalNode(){}
    ~TrigonometryFunctionalNode() override {}

    unsigned int nPorts( PortType portType ) const override;

    ConnectionPolicy portOutConnectionPolicy(PortIndex portIndex) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;
};

class RadiansFunctionalNode : public TrigonometryFunctionalNode {
public:
    RadiansFunctionalNode(){}
    ~RadiansFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;
};

class DegreesFunctionalNode : public TrigonometryFunctionalNode {
public:
    DegreesFunctionalNode(){}
    ~DegreesFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    void inputConnectionCreated(const Connection&) override;

    void inputConnectionDeleted(const Connection&) override;

private:
    QString _dataType;
};

class SinFunctionalNode : public TrigonometryFunctionalNode {
public:
    SinFunctionalNode(){}
    ~SinFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class CosFunctionalNode : public TrigonometryFunctionalNode {
public:
    CosFunctionalNode(){}
    ~CosFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class TanFunctionalNode : public TrigonometryFunctionalNode {
public:
    TanFunctionalNode(){}
    ~TanFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class CtanFunctionalNode : public TrigonometryFunctionalNode {
public:
    CtanFunctionalNode(){}
    ~CtanFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class ArcSinFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcSinFunctionalNode(){}
    ~ArcSinFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class ArcCosFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcCosFunctionalNode(){}
    ~ArcCosFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class ArcTanFunctionalNode : public TrigonometryFunctionalNode {
public:
    ArcTanFunctionalNode(){}
    ~ArcTanFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

///
/// Exponential
///

class PowFunctionalNode : public TrigonometryFunctionalNode {
public:
    PowFunctionalNode(){}
    ~PowFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class ExpFunctionalNode : public TrigonometryFunctionalNode {
public:
    ExpFunctionalNode(){}
    ~ExpFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class Exp2FunctionalNode : public TrigonometryFunctionalNode {
public:
    Exp2FunctionalNode(){}
    ~Exp2FunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class LogFunctionalNode : public TrigonometryFunctionalNode {
public:
    LogFunctionalNode(){}
    ~LogFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

class Log2FunctionalNode : public TrigonometryFunctionalNode {
public:
    Log2FunctionalNode(){}
    ~Log2FunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

/// todo: replace float to universal decimal type
class SqrtFunctionalNode : public TrigonometryFunctionalNode {
public:
    SqrtFunctionalNode(){}
    ~SqrtFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

/// todo: replace float to universal decimal type
class InverseSqrtFunctionalNode : public TrigonometryFunctionalNode {
public:
    InverseSqrtFunctionalNode(){}
    ~InverseSqrtFunctionalNode() override {}

    QString name() const override;

    QString caption() const override;

    QJsonObject save() const override;
};

///
/// Common
///


#endif // FUNCTIONALNODES_HPP

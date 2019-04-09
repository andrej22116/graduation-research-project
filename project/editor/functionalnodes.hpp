#ifndef FUNCTIONALNODES_HPP
#define FUNCTIONALNODES_HPP

#include "BaseShaderNodeDataModel.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;

class FunctionalNode : public BaseShaderNodeDataModel {
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

    std::string whatThis() const override;

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

    std::string whatThis() const override;

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

    std::string whatThis() const override;

    unsigned int nPorts( PortType portType ) const override;

    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override;

    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex ) const override;

    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override;

    ConnectionPolicy portOutConnectionPolicy(PortIndex portIndex) const override;
};
#endif // FUNCTIONALNODES_HPP

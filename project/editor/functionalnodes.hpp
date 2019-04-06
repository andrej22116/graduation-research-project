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
    unsigned int nPorts( PortType portType ) const override final;

    /**
     * @brief dataType
     * @param portType
     * @param portIndex
     * @return Data type for port
     *
     * In/Out types: double
     */
    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override final;

    /**
     * @brief portCaption
     * @param portType
     * @param portIndex
     * @return port name
     */
    QString portCaption( PortType portType
                       , PortIndex portIndex ) const override final;

    /**
     * @brief portCaptionVisible
     * @return only true!
     */
    bool portCaptionVisible( PortType portType
                           , PortIndex portIndex) const override final;

    /**
     * @brief portOutConnectionPolicy
     * @param portIndex
     * @return
     */
    ConnectionPolicy portOutConnectionPolicy(PortIndex portIndex) const override final;

protected:
    /**
     * @brief called from nPorts.
     * @warning First in/out port is busy!
     */
    virtual unsigned int m_nPorts( PortType portType ) const = 0;

    /**
     * @brief called from dataType.
     * @warning First in/out port is busy!
     */
    virtual NodeDataType m_dataType( PortType portType
                                   , PortIndex portIndex ) const = 0;

    /**
     * @brief called from portCaptionVisible.
     * @warning First in/out port is busy!
     */
    virtual bool m_portCaptionVisible( PortType portType
                                     , PortIndex portIndex ) const;

    /**
     * @brief called from portCaption.
     * @warning First in/out port is busy!
     */
    virtual QString m_portCaption( PortType portType
                                 , PortIndex portIndex ) const;

    /**
     * @brief called from portOutConnectionPolicy.
     * @warning First out port is busy!
     */
    virtual ConnectionPolicy m_portOutConnectionPolicy(PortIndex portIndex) const;
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

protected:
    unsigned int m_nPorts( PortType portType ) const override;

    NodeDataType m_dataType( PortType portType
                           , PortIndex portIndex ) const override;

    bool m_portCaptionVisible( PortType portType
                             , PortIndex portIndex ) const override;

    QString m_portCaption( PortType portType
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

protected:
    unsigned int m_nPorts( PortType portType ) const override;

    NodeDataType m_dataType( PortType portType
                           , PortIndex portIndex ) const override;

    bool m_portCaptionVisible( PortType portType
                             , PortIndex portIndex ) const override;

    QString m_portCaption( PortType portType
                         , PortIndex portIndex ) const override;
};

#endif // FUNCTIONALNODES_HPP

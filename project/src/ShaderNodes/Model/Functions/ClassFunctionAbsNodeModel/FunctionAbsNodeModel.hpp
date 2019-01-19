#pragma once

#ifndef FUNCTION_ABS_NODE_MODEL_HPP
#define FUNCTION_ABS_NODE_MODEL_HPP


#include <nodes/NodeDataModel>


using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::NodeValidationState;


class DoubleData;


class FunctionAbsNodeModel : public NodeDataModel {
    std::weak_ptr<DoubleData> _number;
    std::shared_ptr<DoubleData> _result;
    bool test = false;

public:
    FunctionAbsNodeModel();

    /**
     * @brief Name
     * @return Model name
     */
    static QString Name();
    QString name() const override;

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
     * @brief outData
     * @param port
     * @return data pointer from port
     */
    std::shared_ptr<NodeData> outData( PortIndex port ) override;

    /**
     * @brief setInData
     * @param data
     * @param portIndex
     *
     * Set data from ports
     */
    void setInData( std::shared_ptr<NodeData> data
                  , PortIndex portIndex ) override;

    /**
     * @brief embeddedWidget
     * @return node widget
     *
     * This node hasn't widget
     */
    QWidget* embeddedWidget() override;

    /**
     * @brief caption
     * @return Node title
     */
    QString caption() const override;

    /**
     * @brief portCaptionVisible
     * @return true, if need show custom, else false
     */
    bool portCaptionVisible(PortType, PortIndex) const override;

    /**
     * @brief portCaption
     * @param portType
     * @param portIndex
     * @return port name
     */
    QString portCaption(PortType portType, PortIndex portIndex) const override;

    ~FunctionAbsNodeModel() override {};

};


#endif

#pragma once

#ifndef DOUBLE_NODE_MODEL_HPP
#define DOUBLE_NODE_MODEL_HPP


#include <nodes/NodeDataModel>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleValidator>
#include "src/ShaderNodes/DoubleData"


using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::NodeValidationState;

template <PortType nodeType = PortType::Out>
class DoubleNodeModel : public NodeDataModel {
    std::weak_ptr<DoubleData> _number;
    std::shared_ptr<DoubleData> _data;
    QWidget* widget;

public:
    DoubleNodeModel() {
        if ( nodeType == PortType::Out ) {
            auto edit = new QLineEdit();
            edit->setMaxLength(20);
            edit->setValidator(new QDoubleValidator(edit));
            widget = edit;
        }
        else {
            widget = new QLabel();
        }
    }

    /**
     * @brief Name
     * @return Model name
     */
    QString name() const override {
        return nodeType == PortType::In ? "Result Double" : "Source Double";
    };

    /**
     * @brief nPorts
     * @param portType
     * @return ports amount
     *
     * Node have one input port, one output port
     */
    unsigned int nPorts( PortType portType ) const override {
        return portType == nodeType;
    };

    /**
     * @brief dataType
     * @param portType
     * @param portIndex
     * @return Data type for port
     *
     * In/Out types: double
     */
    NodeDataType dataType( PortType portType
                         , PortIndex portIndex ) const override {
        return DoubleData().type();
    }

    /**
     * @brief outData
     * @param port
     * @return data pointer from port
     */
    std::shared_ptr<NodeData> outData( PortIndex port ) override {
        return std::static_pointer_cast<NodeData>(_data);
    }

    /**
     * @brief setInData
     * @param data
     * @param portIndex
     *
     * Set data from ports
     */
    void setInData( std::shared_ptr<NodeData> data
                  , PortIndex portIndex ) override {
        _number = std::dynamic_pointer_cast<DoubleData>(data);
    }

    /**
     * @brief embeddedWidget
     * @return node widget
     *
     * This node hasn't widget
     */
    QWidget* embeddedWidget() override {
        return widget;
    };

    /**
     * @brief caption
     * @return Node title
     */
    QString caption() const override {
        return this->name();
    }

    ~DoubleNodeModel() override {};

};


#endif

#ifndef BASESHADERNODEDATAMODEL_HPP
#define BASESHADERNODEDATAMODEL_HPP

#include <nodes/NodeDataModel>

using QtNodes::NodeDataModel;

class BaseShaderNodeDataModel : public NodeDataModel {
public:
    BaseShaderNodeDataModel() {}

    ~BaseShaderNodeDataModel() override {}

    /**
     * @brief whatThis method should return own name
     * @return type name whithout localization
     */
    virtual std::string whatThis() const = 0;
};

#endif

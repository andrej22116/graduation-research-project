#ifndef NODEDATATYPEFACTORY_HPP
#define NODEDATATYPEFACTORY_HPP

#include <QHash>
#include <QSet>

namespace QtNodes {
    class NodeDataType;
}

using QtNodes::NodeDataType;

class NodeDataTypeFactory
{
    NodeDataTypeFactory();
    NodeDataTypeFactory(const NodeDataTypeFactory&) = delete;
    NodeDataTypeFactory(NodeDataTypeFactory&&) = delete;

    NodeDataTypeFactory&
    operator = (const NodeDataTypeFactory&) = delete;
    NodeDataTypeFactory&
    operator = (NodeDataTypeFactory&&) = delete;

public:
    static NodeDataType
    build(const QString& name);

    static const QSet<QString>&
    supportedTypes();

private:
    static NodeDataTypeFactory&
    instance();

    template<typename DataType>
    void registerDataType() {
        DataType type;
        _supportedTypes += type.name;
        _dataTypes[type.name] = type;
    }

private:
    QHash<QString, NodeDataType> _dataTypes;
    QSet<QString> _supportedTypes;
};

#endif // NODEDATATYPEFACTORY_HPP

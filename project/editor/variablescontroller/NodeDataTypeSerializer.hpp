#ifndef NODEDATATYPESERIALIZER_HPP
#define NODEDATATYPESERIALIZER_HPP

#include <QSet>
#include <QHash>
#include <functional>
#include <memory>

class QJsonValue;
class VariableDataModel;

class NodeDataTypeSerializer
{
    NodeDataTypeSerializer();
    NodeDataTypeSerializer(const NodeDataTypeSerializer&) = delete;
    NodeDataTypeSerializer(NodeDataTypeSerializer&&) = delete;

    NodeDataTypeSerializer&
    operator = (const NodeDataTypeSerializer&) = delete;
    NodeDataTypeSerializer&
    operator = (NodeDataTypeSerializer&&) = delete;

public:
    static const QSet<QString>&
    supportedTypes();

    static QJsonValue
    serialize( const QString& dataType
             , std::shared_ptr<VariableDataModel> dataModel );

    static void
    deserialize( const QJsonValue& json
               , const QString& dataType
               , std::shared_ptr<VariableDataModel> dataModel );

private:
    static NodeDataTypeSerializer&
    instance();

    template<typename DataType, typename GetF, typename SetF>
    void registerDataType(GetF get, SetF set) {
        DataType type;
        _supportedTypes += type.name;
        _serializers[type.name] = {get, set};
    }

private:
    using GetFunction = std::function<
                            QJsonValue(std::shared_ptr<VariableDataModel>) >;
    using SetFunction = std::function<
                            void( const QJsonValue&
                                , std::shared_ptr<VariableDataModel> )>;

    QHash<QString, std::pair<GetFunction, SetFunction>> _serializers;
    QSet<QString> _supportedTypes;
};

#endif // NODEDATATYPESERIALIZER_HPP

#include "NodeDataTypeSerializer.hpp"
#include "ShaderNodeDataTypes.hpp"
#include "VariableDataModels.hpp"

#include <QJsonObject>


template<typename T>
std::shared_ptr<T>
modelToModel(std::shared_ptr<VariableDataModel> model) {
    return std::static_pointer_cast<T>(model);
}


NodeDataTypeSerializer::
NodeDataTypeSerializer()
{
    registerDataType<IntegerDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<IntegerDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonValue value;
        value = QString::number(model->value);

        return value;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<IntegerDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json.toString().toInt();
    });

    registerDataType<UnsignedIntegerDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<UnsignedIntegerDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonValue value;
        value = QString::number(model->value);

        return value;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<UnsignedIntegerDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json.toString().toUInt();
    });

    registerDataType<FloatDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<FloatDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonValue value;
        value = QString::number(static_cast<double>(model->value));

        return value;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<FloatDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = static_cast<float>(json.toString().toDouble());
    });

    registerDataType<DoubleDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<DoubleDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonValue value;
        value = QString::number(model->value);

        return value;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<DoubleDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json.toString().toDouble();
    });

    registerDataType<BooleanDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<BooleanDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonValue value;
        value = QString::number(model->value);

        return value;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<BooleanDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json.toBool();
    });

    registerDataType<Vec2DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["r"] = QString::number(static_cast<double>(model->value[0]));
        obj["g"] = QString::number(static_cast<double>(model->value[1]));

        return obj;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["r"].toString().toDouble());
        model->value[1] = static_cast<float>(json["g"].toString().toDouble());
    });

    registerDataType<Vec3DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["r"] = QString::number(static_cast<double>(model->value[0]));
        obj["g"] = QString::number(static_cast<double>(model->value[1]));
        obj["b"] = QString::number(static_cast<double>(model->value[2]));

        return obj;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["r"].toString().toDouble());
        model->value[1] = static_cast<float>(json["g"].toString().toDouble());
        model->value[2] = static_cast<float>(json["b"].toString().toDouble());
    });

    registerDataType<Vec4DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonValue {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["r"] = QString::number(static_cast<double>(model->value[0]));
        obj["g"] = QString::number(static_cast<double>(model->value[1]));
        obj["b"] = QString::number(static_cast<double>(model->value[2]));
        obj["a"] = QString::number(static_cast<double>(model->value[3]));

        return obj;
    }, []( const QJsonValue& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["r"].toString().toDouble());
        model->value[1] = static_cast<float>(json["g"].toString().toDouble());
        model->value[2] = static_cast<float>(json["b"].toString().toDouble());
        model->value[3] = static_cast<float>(json["a"].toString().toDouble());
    });
}


const QSet<QString>&
NodeDataTypeSerializer::
supportedTypes()
{
    return instance()._supportedTypes;
}


QJsonValue
NodeDataTypeSerializer::
serialize( const QString& dataType
         , std::shared_ptr<VariableDataModel> dataModel )
{
    return instance()._serializers[dataType].first(dataModel);
}


void
NodeDataTypeSerializer::
deserialize( const QJsonValue& json
           , const QString& dataType
           , std::shared_ptr<VariableDataModel> dataModel )
{
    instance()._serializers[dataType].second(json, dataModel);
}


NodeDataTypeSerializer&
NodeDataTypeSerializer::
instance()
{
    static NodeDataTypeSerializer instance;
    return instance;
}

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
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<IntegerDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value"] = model->value;

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<IntegerDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json["value"].toInt();
    });

    registerDataType<UnsignedIntegerDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<UnsignedIntegerDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value"] = QString::number(model->value);

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<UnsignedIntegerDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json["value"].toString().toUInt();
    });

    registerDataType<FloatDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<FloatDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value"] = static_cast<double>(model->value);

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<FloatDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = static_cast<float>(json["value"].toDouble());
    });

    registerDataType<DoubleDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<DoubleDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value"] = model->value;

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<DoubleDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json["value"].toDouble();
    });

    registerDataType<BooleanDataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<BooleanDataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value"] = model->value;

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<BooleanDataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value = json["value"].toBool();
    });

    registerDataType<Vec2DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value_r"] = static_cast<double>(model->value[0]);
        obj["value_g"] = static_cast<double>(model->value[1]);

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["value_r"].toDouble());
        model->value[1] = static_cast<float>(json["value_g"].toDouble());
    });

    registerDataType<Vec3DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value_r"] = static_cast<double>(model->value[0]);
        obj["value_g"] = static_cast<double>(model->value[1]);
        obj["value_b"] = static_cast<double>(model->value[2]);

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["value_r"].toDouble());
        model->value[1] = static_cast<float>(json["value_g"].toDouble());
        model->value[2] = static_cast<float>(json["value_b"].toDouble());
    });

    registerDataType<Vec4DataType>(
        [](std::shared_ptr<VariableDataModel> variable) -> QJsonObject {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return {};
        }

        QJsonObject obj;
        obj["value_r"] = static_cast<double>(model->value[0]);
        obj["value_g"] = static_cast<double>(model->value[1]);
        obj["value_b"] = static_cast<double>(model->value[2]);
        obj["value_a"] = static_cast<double>(model->value[3]);

        return obj;
    }, []( const QJsonObject& json
         , std::shared_ptr<VariableDataModel> variable ) {
        auto model = modelToModel<Vec2DataModel>(variable);
        if ( !model ) {
            return;
        }

        model->value[0] = static_cast<float>(json["value_r"].toDouble());
        model->value[1] = static_cast<float>(json["value_g"].toDouble());
        model->value[2] = static_cast<float>(json["value_b"].toDouble());
        model->value[3] = static_cast<float>(json["value_a"].toDouble());
    });
}


const QSet<QString>&
NodeDataTypeSerializer::
supportedTypes()
{
    return instance()._supportedTypes;
}


QJsonObject
NodeDataTypeSerializer::
serialize( const QString& dataType
         , std::shared_ptr<VariableDataModel> dataModel )
{
    return instance()._serializers[dataType].first(dataModel);
}


void
NodeDataTypeSerializer::
deserialize( const QJsonObject& json
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

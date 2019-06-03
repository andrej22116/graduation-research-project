#ifndef VARIABLEDATAMODELSFACTORY_HPP
#define VARIABLEDATAMODELSFACTORY_HPP

#include <QString>
#include <QHash>
#include <QSet>
#include <functional>
#include "VariableDataModels.hpp"

class VariableDataModelsFactory
{
    VariableDataModelsFactory();
    VariableDataModelsFactory(const VariableDataModelsFactory&) = delete;
    VariableDataModelsFactory(VariableDataModelsFactory&&) = delete;

    VariableDataModelsFactory&
    operator = (const VariableDataModelsFactory&) = delete;
    VariableDataModelsFactory&
    operator = (VariableDataModelsFactory&&) = delete;

public:
    using VariableDataModelPtr = std::shared_ptr<VariableDataModel>;

    static VariableDataModelPtr
    build(const QString& name);

    static const QSet<QString>&
    supportedTypes();

private:
    static VariableDataModelsFactory&
    instance();

    template<typename DataType, typename DataModel>
    void registerDataType() {
        DataType type;
        _supportedTypes += type.name;
        _varFactories[type.name] = []() {
            return std::make_shared<DataModel>();
        };
    }

private:
    QHash<QString, std::function<VariableDataModelPtr()>> _varFactories;
    QSet<QString> _supportedTypes;
};

#endif // VARIABLEDATAMODELSFACTORY_HPP

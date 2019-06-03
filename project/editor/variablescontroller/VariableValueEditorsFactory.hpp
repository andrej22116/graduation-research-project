#ifndef VARIABLEEDITORSPOOL_HPP
#define VARIABLEEDITORSPOOL_HPP

#include <QWidget>
#include <QSet>
#include <memory>
#include <functional>

class VariableValueEditor;

class VariableValueEditorsFactory
{
    VariableValueEditorsFactory();
    VariableValueEditorsFactory(const VariableValueEditorsFactory&) = delete;
    VariableValueEditorsFactory(VariableValueEditorsFactory&&) = delete;

    VariableValueEditorsFactory&
    operator = (const VariableValueEditorsFactory&) = delete;
    VariableValueEditorsFactory&
    operator = (VariableValueEditorsFactory&&) = delete;

public:
    static VariableValueEditor*
    build(const QString& modelDataTypeName);

    static const QSet<QString>&
    supportedTypes();

private:
    static VariableValueEditorsFactory&
    instance();

    template<typename DataType, typename DataModel>
    void registerDataType() {
        DataType type;
        _supportedTypes += type.name;
        _variableEditors[type.name] = []() {
            return new DataModel();
        };
    }

private:
    using Factory = std::function<VariableValueEditor*()>;
    QHash<QString, Factory> _variableEditors;
    QSet<QString> _supportedTypes;
};

#endif // VARIABLEEDITORSPOOL_HPP

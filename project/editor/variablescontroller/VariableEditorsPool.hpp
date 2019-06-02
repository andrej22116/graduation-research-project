#ifndef VARIABLEEDITORSPOOL_HPP
#define VARIABLEEDITORSPOOL_HPP

#include <QWidget>
#include <QSet>
#include <memory>

class VariableEditor;

class VariableEditorsPool
{
    VariableEditorsPool();
    VariableEditorsPool(const VariableEditorsPool&) = delete;
    VariableEditorsPool(VariableEditorsPool&&) = delete;

    VariableEditorsPool&
    operator = (const VariableEditorsPool&) = delete;
    VariableEditorsPool&
    operator = (VariableEditorsPool&&) = delete;

public:
    using VariableEditorPtr = std::shared_ptr<VariableEditor>;

    static VariableEditorPtr
    editor(const QString& modelDataTypeName);

    static const QSet<QString>&
    supportedTypes();

private:
    static VariableEditorsPool&
    instance();

private:
    QSet<QString> _supportedTypes;
};

#endif // VARIABLEEDITORSPOOL_HPP

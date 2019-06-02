#include "VariableEditorsPool.hpp"

VariableEditorsPool::
VariableEditorsPool()
{

}

VariableEditorsPool::VariableEditorPtr
VariableEditorsPool::
editor(const QString& modelDataTypeName)
{
    return nullptr;
}

const QSet<QString>&
VariableEditorsPool::
supportedTypes()
{
    return instance()._supportedTypes;
}

VariableEditorsPool&
VariableEditorsPool::
instance()
{
    static VariableEditorsPool instance;
    return instance;
}

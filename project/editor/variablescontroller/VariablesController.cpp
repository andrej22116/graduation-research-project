#include "VariablesController.hpp"
#include <nodes/NodeDataModel>

#include "VariableDataModelsFactory.hpp"
#include "VariableEditorsPool.hpp"

using QtNodes::NodeDataModel;

static const QString NAME_IS_EMPTY_MESSAGE = "Variable name cann't be empty!";
static const QString NAME_IS_TAKEN_MESSAGE = "Variable name %1 is taken!";
static const QString NAME_IS_RESERVED_MESSAGE = "Variable name %1 is reserved!";

VariablesController::
VariablesController()
{

}

QStringList
VariablesController::
defaultVariablesNames()
{
    return _defaultVariables.keys();
}


QStringList
VariablesController::
variablesNames()
{
    return _variables.keys();
}


QStringList
VariablesController::
supportedVariablesTypes()
{
    auto supportedDataModels = VariableDataModelsFactory::supportedTypes();
    auto supportedDataEditors = VariableEditorsPool::supportedTypes();
    return (supportedDataModels & supportedDataEditors).toList();
}


QWidget*
VariablesController::
getVariableEditor(const QString& name)
{
    return nullptr;
}


void
VariablesController::
onCreateVariable(const QString& name)
{
    if ( _variables.find(name) != _variables.end() ) {
        emit variableControllerError(NAME_IS_TAKEN_MESSAGE.arg(name));
        return;
    }
    else if ( _defaultVariables.find(name) != _defaultVariables.end() ) {
        emit variableControllerError(NAME_IS_RESERVED_MESSAGE.arg(name));
        return;
    }

    auto typeName = *VariableDataModelsFactory::supportedTypes().begin();
    _variables[name] = VariableDataModelsFactory::build(typeName);
    _variablesTypes[name] = typeName;
}


void
VariablesController::
onRenameVariable( const QString& oldName
                , const QString& newName )
{
    if ( _variables.find(newName) != _variables.end() ) {
        emit variableControllerError(NAME_IS_TAKEN_MESSAGE.arg(newName));
        return;
    }
    else if ( _defaultVariables.find(newName) != _defaultVariables.end() ) {
        emit variableControllerError(NAME_IS_RESERVED_MESSAGE.arg(newName));
        return;
    }

    _variables[newName] = _variables[oldName];
    _variablesTypes[newName] = _variablesTypes[oldName];

    _variables.remove(oldName);
    _variablesTypes.remove(oldName);
}


void
VariablesController::
onRemoveVariable(const QString& name)
{
    _variables.remove(name);
    _defaultVariables.remove(name);
    _variablesTypes.remove(name);
}


void
VariablesController::
onChangeVariableDataModel( const QString& variableName
                         , const QString& dataModelName )
{
    _variables[variableName] = VariableDataModelsFactory::build(dataModelName);
    _variablesTypes[variableName] = dataModelName;
}


void
VariablesController::
onAddDefaultVariableToScene( const QString& name
                           , const QString& typeName
                           , std::shared_ptr<VariableDataModel> data )
{
    /// todo: add editor scene to contructor;
}


void
VariablesController::
onAddVariableToScene(const QString& name)
{
    /// todo: add editor scene to contructor;
}

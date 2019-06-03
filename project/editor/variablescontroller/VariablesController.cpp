#include "VariablesController.hpp"
#include <nodes/NodeDataModel>
#include <nodes/Node>
#include <QUuid>

#include "VariableDataModelsFactory.hpp"
#include "VariableValueEditorsFactory.hpp"
#include "NodeDataTypeFactory.hpp"
#include "nodes/VariableNode.hpp"

#include "EditorGraphicsScene.hpp"
#include <nodes/FlowView>

using QtNodes::NodeDataModel;

static const QString NAME_IS_EMPTY_MESSAGE = "Variable name cann't be empty!";
static const QString NAME_IS_TAKEN_MESSAGE = "Variable name %1 is taken!";
static const QString NAME_IS_RESERVED_MESSAGE = "Variable name %1 is reserved!";

VariablesController::
VariablesController( FlowViewPtr view
                   , EditorGraphicsScenePtr scene )
    : _view(view)
    , _scene(scene)
{
    auto supportedDataModels = VariableDataModelsFactory::supportedTypes();
    auto supportedDataEditors = VariableValueEditorsFactory::supportedTypes();
    _supportedVariablesTypes = (supportedDataModels & supportedDataEditors)
                               .toList();

    connect( scene.get()
           , &EditorGraphicsScene::nodeDeleted
           , this
           , &VariablesController::onRemoveVariableNodeFromScene);
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


const QStringList&
VariablesController::
supportedVariablesTypes()
{
    return _supportedVariablesTypes;
}


QWidget*
VariablesController::
getVariableEditor(const QString& name)
{
    return nullptr;
}


void
VariablesController::
onSelectVariable(const QString& name)
{
    auto variableDataModel = _variables[name];
    auto variableTypeName = _variablesTypes[name];

    emit variableSelected(variableDataModel, variableTypeName);
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

    auto typeName = supportedVariablesTypes()[0];
    auto variable = VariableDataModelsFactory::build(typeName);
    variable->name = name;
    variable->isConst = false;
    variable->canBeEdited = true;
    _variables[name] = variable;

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
    _variablesNodesIds[newName] = _variablesNodesIds[oldName];

    for ( auto id : _variablesNodesIds[newName]) {
        _nodesIdAssociate[id] = newName;
        static_cast<VariableNode*>(_nodesDataModels[id])->setName(newName);
    }

    _variables.remove(oldName);
    _variablesTypes.remove(oldName);
    _variablesNodesIds.remove(oldName);

    emit variableChangeName(oldName, newName);
}


void
VariablesController::
onRemoveVariable(const QString& name)
{
    _variables.remove(name);
    _defaultVariables.remove(name);
    _variablesTypes.remove(name);

    auto ids = _variablesNodesIds[name];
    for ( auto id : ids) {
        auto& node = *(_scene->nodes().at(id));
        _scene->removeNode(node);
        //onRemoveVariableNodeFromScene(node);
    }

    _variablesNodesIds.remove(name);
}


void
VariablesController::
onChangeVariableDataModel( const QString& variableName
                         , const QString& dataModelName )
{
    auto newDataModel = VariableDataModelsFactory::build(dataModelName);
    auto oldDataModel = _variables[variableName];
    newDataModel->name = oldDataModel->name;
    newDataModel->isConst = oldDataModel->isConst;
    newDataModel->logickType = oldDataModel->logickType;
    newDataModel->canBeEdited = oldDataModel->canBeEdited;

    _variables[variableName] = newDataModel;
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
    auto variableType = _variablesTypes[name];
    auto dataType = NodeDataTypeFactory::build(variableType);
    auto dataModelPtr = std::make_unique<VariableNode>(name, dataType);
    if ( !dataModelPtr ) {
        return;
    }
    auto& node = _scene->createNode(std::move(dataModelPtr));
    auto& graphicsObject = node.nodeGraphicsObject();
    graphicsObject.setPos(
                _view->mapToScene(
                    _view->viewport()->rect().center()));

    _variablesNodesIds[name] += node.id();
    _nodesIdAssociate[node.id()] = name;
    _nodesDataModels[node.id()] = node.nodeDataModel();
}


void
VariablesController::
onRemoveVariableNodeFromScene(QtNodes::Node& node)
{
    auto id = node.id();
    _variablesNodesIds[_nodesIdAssociate[id]].remove(id);
    _nodesIdAssociate.remove(id);
    _nodesDataModels.remove(id);
}


QJsonObject
VariablesController::
save() const
{
    //QJsonObject obj;


    return {
    };
}


void
VariablesController::
restore(const QJsonObject&)
{
}

#include "VariablesController.hpp"
#include <nodes/NodeDataModel>
#include <nodes/Node>
#include <QUuid>
#include <QJsonArray>
#include <QJsonObject>

#include "VariableDataModelsFactory.hpp"
#include "VariableValueEditorsFactory.hpp"
#include "NodeDataTypeFactory.hpp"
#include "nodes/VariableNode/VariableNode.hpp"

#include "EditorGraphicsScene.hpp"
#include <nodes/FlowView>
#include "variablescontroller/NodeDataTypeSerializer.hpp"

#include "ShaderNodeDataTypes.hpp"

using QtNodes::NodeDataModel;

static const QString NAME_IS_EMPTY_MESSAGE = "Variable name cann't be empty!";
static const QString NAME_IS_TAKEN_MESSAGE = "Variable name \"%1\" is taken!";
static const QString NAME_IS_RESERVED_MESSAGE = "Variable name \"%1\" is reserved!";

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

    {
        Vec4DataType vec4;
        Vec3DataType vec3;
        Vec2DataType vec2;
        UnsignedIntegerDataType unsignedInt;
        createDefaultVariable("Result color", vec4.name);
        createDefaultVariable("Time", unsignedInt.name);
        createDefaultVariable("Vertex", vec3.name);
        createDefaultVariable("Normal", vec3.name);
        createDefaultVariable("Tangent", vec3.name);
        createDefaultVariable("Bitangent", vec3.name);
        createDefaultVariable("UV position", vec2.name);
    }
}

QStringList
VariablesController::
defaultVariablesNames()
{
    return _defaultVariables.toList();
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

    auto dataType = NodeDataTypeFactory::build(dataModelName);

    for ( auto id : _variablesNodesIds[variableName]) {
        static_cast<VariableNode*>(_nodesDataModels[id])->setDataType(dataType);
    }
}


void
VariablesController::
addVariableToScene(const QString& name)
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


bool
VariablesController::
createUserVariable(const QString& name)
{
    if ( variableNameExists(name) ) {
        return false;
    }

    auto typeName = supportedVariablesTypes()[0];
    auto variable = VariableDataModelsFactory::build(typeName);
    variable->name = name;
    variable->isConst = false;
    variable->canBeEdited = true;
    _variables[name] = variable;

    _variablesTypes[name] = typeName;

    return true;
}


void
VariablesController::
createUserVariableWithSignal(const QString& name)
{
    if ( createUserVariable(name) ) {
        emit createdNewUserVariable(name);
    }
}


bool
VariablesController::
renameUserVariable( const QString& oldName
                  , const QString& newName )
{
    if ( variableNameExists(newName) ) {
        return false;
    }

    _variables[newName] = _variables[oldName];
    _variables.remove(oldName);

    renameVariable(oldName, newName);

    return true;
}


void
VariablesController::
renameUserVariableWithSignal( const QString& oldName
                            , const QString& newName )
{
    if ( renameUserVariable(oldName, newName) ) {
        emit renamedUserVariable(oldName, newName);
    }
}


bool VariablesController::
removeUserVariable(const QString& name)
{
    if (  _variables.find(name) == _variables.end() ) {
        return false;
    }

    _variables.remove(name);
    removeVariable(name);

    return true;
}


void VariablesController::
removeUserVariableWithSignal(const QString& name)
{
    if ( removeUserVariable(name) ) {
        emit removedUserVariable(name);
    }
}


bool
VariablesController::
createDefaultVariable( const QString& name
                     , const QString& typeName )
{
    if ( variableNameExists(name) ) {
        return false;
    }

    _defaultVariables += name;
    _variablesTypes[name] = typeName;

    return true;
}


void
VariablesController::
createDefaultVariableWithSignal( const QString& name
                               , const QString& typeName )
{
    if ( createDefaultVariable(name, typeName) ) {
        emit createdNewDefaultVariable(name);
    }
}


bool
VariablesController::
renameDefaultVariable( const QString& oldName
                     , const QString& newName )
{
    if ( variableNameExists(newName) ) {
        return false;
    }

    _defaultVariables.remove(oldName);
    _defaultVariables += newName;
    renameVariable(oldName, newName);

    return true;
}


void
VariablesController::
renameDefaultVariableWithSignal( const QString& oldName
                               , const QString& newName )
{
    if ( renameDefaultVariable(oldName, newName) ) {
        emit renamedDefaultVariable(oldName, newName);
    }
}


bool
VariablesController::
removeDefaultVariable(const QString& name)
{
    if (  _defaultVariables.find(name) == _defaultVariables.end() ) {
        return false;
    }

    _defaultVariables.remove(name);
    removeVariable(name);

    return true;
}


void
VariablesController::
removeDefaultVariableWithSignal(const QString& name)
{
    if ( removeDefaultVariable(name) ) {
        emit removedDefaultVariable(name);
    }
}


bool
VariablesController::
variableNameExists(const QString& name)
{
    if ( _variables.find(name) != _variables.end() ) {
        emit variableControllerError(NAME_IS_TAKEN_MESSAGE.arg(name));
        return true;
    }
    else if ( _defaultVariables.find(name) != _defaultVariables.end() ) {
        emit variableControllerError(NAME_IS_RESERVED_MESSAGE.arg(name));
        return true;
    }

    return false;
}


void
VariablesController::
renameVariable( const QString& oldName
              , const QString& newName)
{
    _variablesTypes[newName] = _variablesTypes[oldName];
    _variablesNodesIds[newName] = _variablesNodesIds[oldName];

    for ( auto id : _variablesNodesIds[newName]) {
        _nodesIdAssociate[id] = newName;
        static_cast<VariableNode*>
                (_nodesDataModels[id])->setVariableName(newName);
    }

    _variablesTypes.remove(oldName);
    _variablesNodesIds.remove(oldName);
}


void
VariablesController::
removeVariable( const QString& name )
{
    _variablesTypes.remove(name);

    auto ids = _variablesNodesIds[name];
    for ( auto id : ids) {
        auto& node = *(_scene->nodes().at(id));
        _scene->removeNode(node);
    }

    _variablesNodesIds.remove(name);
}


QJsonArray
VariablesController::
save() const
{
    QJsonArray array;

    for ( auto& variable : _variables.keys() ) {
        QJsonObject obj;
        obj["name"] = variable;
        obj["type"] = _variablesTypes[variable];

        auto value = NodeDataTypeSerializer::serialize( _variablesTypes[variable]
                                                      , _variables[variable] );

        obj["value"] = value;

        array.push_back(obj);
    }

    return array;
}


void
VariablesController::
restore(const QJsonArray& array)
{
    for ( auto variable : array ) {
        auto varObj = variable.toObject();
        auto name = varObj["name"].toString();
        auto type = varObj["type"].toString();

        createUserVariableWithSignal(name);
        onChangeVariableDataModel(name, type);

        NodeDataTypeSerializer::deserialize( varObj["value"].toObject()
                                           , type
                                           , _variables[name]);
    }

    QVector<QtNodes::Node*> blackList;

    _scene->iterateOverNodes([&](QtNodes::Node* node){
        auto variableModel = dynamic_cast<VariableNode*>
                             (node->nodeDataModel());
        if ( !variableModel ) {
            return;
        }

        auto variableName = variableModel->variableName();

        if ( _variables.find(variableName) == _variables.end()
             && _defaultVariables.find(variableName) == _defaultVariables.end()) {
            blackList.push_back(node);
            return;
        }

        _variablesNodesIds[variableName] += node->id();
        _nodesIdAssociate[node->id()] = variableName;
        _nodesDataModels[node->id()] = node->nodeDataModel();
    });


    for ( auto& node : blackList ) {
        _scene->removeNode(*node);
    }
}

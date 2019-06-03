#include "EditorController.hpp"

#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <nodesstore/NodeStoreWidget.hpp>
#include <variablescontroller/VariablesControllerWidget.hpp>
#include <nodesmodels/DefaultDataModelRegistry.hpp>
#include <EditorGraphicsScene.hpp>

#include "variablescontroller/VariablesController.hpp"

EditorController::
EditorController(QObject *parent)
    : QObject(parent)
    , _dataModelRegistry(new DefaultDataModelRegistry)
    , _scene(new EditorGraphicsScene(_dataModelRegistry, this))
    , _view(new QtNodes::FlowView(_scene.get()))
    , _variableController(new VariablesController(_view, _scene))
{
    QtNodes::ConnectionStyle::setConnectionStyle(
    R"(
      {
        "ConnectionStyle": {
          "UseDataDefinedColors": true
        }
      }
      )");

    _nodeStoreWidget = std::make_shared<NodeStoreWidget>(_dataModelRegistry);
    _variablesControllerWidget =
            std::make_shared<VariablesControllerWidget>(_variableController);
}


QWidget*
EditorController::
editor()
{
    return _view.get();
}

QWidget*
EditorController::
variables()
{
    return _variablesControllerWidget.get();
}

QWidget*
EditorController::
nodesStore()
{
    return _nodeStoreWidget.get();
}


QJsonObject
EditorController::
save() const
{
    return {};
}


void
EditorController::
restore(const QJsonObject&)
{
}

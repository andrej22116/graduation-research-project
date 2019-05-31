#include "EditorController.hpp"

#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <nodesstore/NodeStoreWidget.hpp>
#include <nodesmodels/DefaultDataModelRegistry.hpp>
#include <EditorGraphicsScene.hpp>

EditorController::
EditorController(QObject *parent)
    : QObject(parent)
    , _dataModelRegistry(new DefaultDataModelRegistry)
    , _flowScene(new EditorGraphicsScene(_dataModelRegistry, this))
    , _flowView(new QtNodes::FlowView(_flowScene.get()))
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
}


QWidget*
EditorController::
editor()
{
    return _flowView.get();
}

QWidget*
EditorController::
variables()
{
    return nullptr;
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
#include "EditorController.hpp"

#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <nodesstore/NodeStoreWidget.hpp>
#include <variablescontroller/VariablesControllerWidget.hpp>
#include <nodesmodels/DefaultDataModelRegistry.hpp>
#include <EditorGraphicsScene.hpp>

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>

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

    _dataModelRegistry->postRegisterModels();
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


void
EditorController::
save(const QString& path) const
{
    if (!path.isEmpty())
    {
        auto nodesObj = _scene->toJson();
        nodesObj["variables"] = _variableController->save();

        QFile file(path);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(QJsonDocument{nodesObj}.toJson());
        }
    }
}


void
EditorController::
restore(const QString& path)
{
    if (!QFileInfo::exists(path))
      return;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
      return;

    QByteArray wholeFile = file.readAll();
    QJsonObject const jsonDocument = QJsonDocument::fromJson(wholeFile)
                                     .object();

    _scene->clearScene();
    _scene->fromJson(jsonDocument);

    _variableController->restore(jsonDocument["variables"].toArray());
}


void
EditorController::
onBeginCompiling()
{
    auto nodesObj = _scene->toJson();
    nodesObj["variables"] = _variableController->save();

    auto sources = std::make_shared<QJsonObject>(std::move(nodesObj));

    emit compile(sources);
}

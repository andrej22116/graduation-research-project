#ifndef EDITORCONTROLLER_HPP
#define EDITORCONTROLLER_HPP

#include <QObject>
#include <memory>

#include <nodes/internal/Serializable.hpp>

namespace QtNodes {
    class FlowView;
    class DataModelRegistry;
}

using QtNodes::FlowView;
using QtNodes::DataModelRegistry;
using QtNodes::Serializable;


class VariablesController;
class NodeStoreWidget;
class VariablesControllerWidget;
class EditorGraphicsScene;

class EditorController : public QObject
                       , public Serializable
{
    Q_OBJECT

public:
    explicit
    EditorController(QObject* parent = nullptr);

    QWidget*
    editor();

    QWidget*
    variables();

    QWidget*
    nodesStore();

public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

private:


private:
    using FlowViewPtr = std::shared_ptr<FlowView>;
    using EditorGraphicsScenePtr = std::shared_ptr<EditorGraphicsScene>;
    using DataModelRegistryPtr = std::shared_ptr<DataModelRegistry>;
    using VariablesControllerPtr = std::shared_ptr<VariablesController>;
    using NodeStoreWidgetPtr = std::shared_ptr<NodeStoreWidget>;
    using VariablesControllerWidgetPtr =
            std::shared_ptr<VariablesControllerWidget>;

    DataModelRegistryPtr _dataModelRegistry;
    EditorGraphicsScenePtr _scene;
    FlowViewPtr _view;
    VariablesControllerPtr _variableController;
    NodeStoreWidgetPtr _nodeStoreWidget;
    VariablesControllerWidgetPtr _variablesControllerWidget;
};

#endif // EDITORCONTROLLER_HPP

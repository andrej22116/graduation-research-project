#ifndef EDITORCONTROLLER_HPP
#define EDITORCONTROLLER_HPP

#include <QObject>
#include <memory>

namespace QtNodes {
    class FlowView;
}

using QtNodes::FlowView;

class VariablesController;
class NodeStoreWidget;
class VariablesControllerWidget;
class EditorGraphicsScene;
class DefaultDataModelRegistry;

class EditorController : public QObject
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
    void
    save(const QString& path) const;

    void
    restore(const QString& path);

private:


private:
    using FlowViewPtr = std::shared_ptr<FlowView>;
    using EditorGraphicsScenePtr = std::shared_ptr<EditorGraphicsScene>;
    using DataModelRegistryPtr = std::shared_ptr<DefaultDataModelRegistry>;
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

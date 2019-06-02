#ifndef EDITORCONTROLLER_HPP
#define EDITORCONTROLLER_HPP

#include <QObject>
#include <memory>

#include <nodes/internal/Serializable.hpp>

namespace QtNodes {
    class FlowScene;
    class FlowView;
    class DataModelRegistry;
}

using QtNodes::FlowView;
using QtNodes::FlowScene;
using QtNodes::DataModelRegistry;
using QtNodes::Serializable;


class VariableController;
class NodeStoreWidget;
class VariablesControllerWidget;

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
    using FlowScenePtr = std::shared_ptr<FlowScene>;
    using DataModelRegistryPtr = std::shared_ptr<DataModelRegistry>;
    using VariableControllerPtr = std::shared_ptr<VariableController>;
    using NodeStoreWidgetPtr = std::shared_ptr<NodeStoreWidget>;
    using VariablesControllerWidgetPtr =
            std::shared_ptr<VariablesControllerWidget>;

    DataModelRegistryPtr _dataModelRegistry;
    FlowScenePtr _flowScene;
    FlowViewPtr _flowView;
    VariableControllerPtr _variableController;
    NodeStoreWidgetPtr _nodeStoreWidget;
    VariablesControllerWidgetPtr _variablesControllerWidget;
};

#endif // EDITORCONTROLLER_HPP

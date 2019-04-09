#include "EditorGraphicsScene.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

#include <nodes/DataModelRegistry>
#include <nodes/Node>

#include <QDataStream>
#include <unordered_map>


EditorGraphicsScene::EditorGraphicsScene( std::shared_ptr<QtNodes::DataModelRegistry> registry
                                        , QObject* parent) :
    QtNodes::FlowScene(registry, parent)
{

}

EditorGraphicsScene::EditorGraphicsScene(QObject* parent) :
    QtNodes::FlowScene(parent)
{
}

void EditorGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    if ( event->mimeData()->hasFormat("ShaderNodes/Node") ) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void EditorGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    if ( event->mimeData()->hasFormat("ShaderNodes/Node") ) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void EditorGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    if ( event->mimeData()->hasFormat("ShaderNodes/Node") ) {
        auto data = event->mimeData()->data("ShaderNodes/Node");
        QDataStream stream( &data, QIODevice::ReadOnly );
        QString dataModelName;
        stream >> dataModelName;

        auto registeredModelsFactories = registry().registeredModelCreators();
        auto& node = createNode(registeredModelsFactories[dataModelName]());

        node.nodeGraphicsObject().setPos(event->scenePos());
        nodePlaced(node);

        event->accept();
    }
    else {
        event->ignore();
    }
}

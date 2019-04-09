#ifndef EDITORGRAPHICSSCENE_HPP
#define EDITORGRAPHICSSCENE_HPP

#include <nodes/FlowScene>

namespace QtNodes {
    class DataModelRegistry;
}

using QtNodes::DataModelRegistry;

class EditorGraphicsScene : public QtNodes::FlowScene
{
public:
    EditorGraphicsScene( std::shared_ptr<DataModelRegistry> registry
                       , QObject* parent = nullptr);

    EditorGraphicsScene(QObject* parent = nullptr);

    ~EditorGraphicsScene() override {}

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;

    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;

    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
};

#endif // EDITORGRAPHICSSCENE_HPP

#ifndef NODEWIDGET_HPP
#define NODEWIDGET_HPP

#include <QWidget>
#include <memory>

class QPixmap;

namespace QtNodes {
    class Node;
    class DataModelRegistry;
}

class NodeWidget : public QWidget
{
public:
    explicit NodeWidget( QtNodes::Node& node
                       , QtNodes::DataModelRegistry& registry
                       , QWidget* parent = nullptr );

    ~NodeWidget() override {}

protected:
    void paintEvent (QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

private:
    std::shared_ptr<QPixmap> _nodePixmap;
    QString _nodeName;
};

#endif // NODEWIDGET_HPP

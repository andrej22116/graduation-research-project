#include "NodeWidget.hpp"
#include <nodes/NodePainter>
#include <nodes/Node>
#include <nodes/DataModelRegistry>

#include <QScrollBar>

#include <QPainter>
#include <QPixmap>

#include <QPaintEvent>
#include <QMouseEvent>

#include <QDrag>
#include <QMimeData>

#include <QByteArray>
#include <QDataStream>

using QtNodes::Node;
using QtNodes::DataModelRegistry;

NodeWidget::NodeWidget( Node& node
                      , DataModelRegistry& registry
                      , QWidget* parent) :
    QWidget(parent)
{
    auto geometry = node.nodeGeometry();
    geometry.recalculateSize(false);
    auto pointDiameter = node.nodeDataModel()->nodeStyle().ConnectionPointDiameter;
    auto twoPointsDiameter = static_cast<qreal>(pointDiameter * 2);
    auto fourPointsDiameter = static_cast<unsigned int>(pointDiameter * 4);
    QSize size( static_cast<int>(geometry.width() + fourPointsDiameter)
              , static_cast<int>(geometry.height() + fourPointsDiameter));

    _nodePixmap = std::make_shared<QPixmap>(size);
    _nodePixmap->fill(Qt::transparent);

    setFixedSize(size);

    QPainter nodePainter;
    nodePainter.begin(_nodePixmap.get());

    nodePainter.translate(twoPointsDiameter, twoPointsDiameter);
    nodePainter.setRenderHint(QPainter::RenderHint::Antialiasing);

    QtNodes::NodePainter::paint(&nodePainter, node, registry, false);

    nodePainter.end();

    _nodeName = node.nodeDataModel()->name();
}

void NodeWidget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);

    painter.setBackgroundMode(Qt::BGMode::TransparentMode);
    painter.drawPixmap(_nodePixmap->rect(), *_nodePixmap, _nodePixmap->rect());

    painter.end();
}

void NodeWidget::mousePressEvent(QMouseEvent*)
{
    auto drag = new QDrag(this);
    auto mimeData = new QMimeData();

    QByteArray data;
    QDataStream stream( &data, QIODevice::WriteOnly );
    stream << _nodeName;

    mimeData->setData("ShaderNodes/Node", data);
    drag->setMimeData(mimeData);
    drag->setPixmap(_nodePixmap->copy());

    drag->exec();
}

#include "VectorConnectGraphicsItem.hpp"
#include <QPainter>
#include "VectorConverterStyle.hpp"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include "VectorPointGraphicsItem.hpp"
#include <QGraphicsDropShadowEffect>
#include <QPainterPathStroker>

VectorConnectGraphicsItem::
VectorConnectGraphicsItem( QGraphicsScene* scene
                         , VectorPointGraphicsItem* from
                         , PointValueType pointValueType )
    : _beginPoint(from->pos())
    , _endPoint(_beginPoint)
    , _pointValueType(pointValueType)
    , _from(from)
    , _to(nullptr)
    , _scene(scene)
{
    setZValue(-1.0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setAcceptHoverEvents(true);

    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(VectorConverterStyle::pointColor(_pointValueType));
    effect->setOffset({0,0});
    effect->setBlurRadius(8);
    setGraphicsEffect(effect);
}


QRectF
VectorConnectGraphicsItem::
boundingRect() const
{

    QRectF basicRect = QRectF(_beginPoint, _endPoint).normalized();

    QRectF c1c2Rect = QRectF(_beginPoint, _endPoint).normalized();

    QRectF commonRect = basicRect.united(c1c2Rect);

    QPointF const cornerOffset(4, 4);

    commonRect.setTopLeft(commonRect.topLeft() - cornerOffset);
    commonRect.setBottomRight(commonRect.bottomRight() + 2 * cornerOffset);

    return commonRect;
}


void
VectorConnectGraphicsItem::
paint( QPainter* painter
     , const QStyleOptionGraphicsItem* option
     , QWidget* )
{
    painter->setClipRect(option->exposedRect);

    painter->setRenderHint(QPainter::RenderHint::Antialiasing, true);
    painter->setPen(VectorConverterStyle::pointPen(_pointValueType));
    painter->drawPath(_linePath);
}


VectorPointGraphicsItem*
VectorConnectGraphicsItem::
pointFrom()
{
    return _from;
}


VectorPointGraphicsItem*
VectorConnectGraphicsItem::
pointTo()
{
    return _to;
}


void
VectorConnectGraphicsItem::
calculatePath()
{
    _linePath = QPainterPath{_beginPoint};
    _linePath.cubicTo( { _endPoint.x() / 2, _beginPoint.y() }
                     , { _beginPoint.x() / 2, _endPoint.y() }
                       , _endPoint);
}


void
VectorConnectGraphicsItem::
deleteThis()
{
    emit beforeDestroy(this);
    _scene->removeItem(this);
    delete this;
}


void
VectorConnectGraphicsItem::
mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    deleteThis();
}


void
VectorConnectGraphicsItem::
mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    _endPoint = event->pos();
    calculatePath();
    update();
}


void
VectorConnectGraphicsItem::
mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    this->ungrabMouse();

    auto items = _scene->items( _endPoint
                              , Qt::IntersectsItemShape
                              , Qt::DescendingOrder );

    if ( !items.empty() )
    {
        QGraphicsItem* graphicsItem = items.front();
        _to = dynamic_cast<VectorPointGraphicsItem*>(graphicsItem);
    }

    if ( items.empty() || !_to ){
        deleteThis();
    }
    else {
        _endPoint = _to->pos();
        calculatePath();
        graphicsEffect()->setEnabled(false);
        update();

        emit addConnection(this);
    }
}


QPainterPath
VectorConnectGraphicsItem::
shape() const
{
    QPainterPathStroker linePathStroker;
    linePathStroker.setWidth(8);

    return linePathStroker.createStroke(_linePath);
}


void
VectorConnectGraphicsItem::
hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    graphicsEffect()->setEnabled(true);
}


void
VectorConnectGraphicsItem::
hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    graphicsEffect()->setEnabled(false);
}

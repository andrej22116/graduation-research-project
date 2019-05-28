#ifndef VECTORCONNECTGRAPHICSITEM_HPP
#define VECTORCONNECTGRAPHICSITEM_HPP

#include <QGraphicsObject>
#include "VectorConverterTypes.hpp"

class VectorPointGraphicsItem;

class VectorConnectGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    VectorConnectGraphicsItem( QGraphicsScene* scene
                             , VectorPointGraphicsItem* from
                             , PointValueType pointValueType );

    // QGraphicsItem interface
public:
    QRectF
    boundingRect() const override;

    QPainterPath
    shape() const override;

    void
    paint( QPainter* painter
         , const QStyleOptionGraphicsItem* option
         , QWidget* widget) override;

    VectorPointGraphicsItem*
    pointFrom();

    VectorPointGraphicsItem*
    pointTo();


signals:
    void
    beforeDestroy(VectorConnectGraphicsItem* item);

    void
    addConnection(VectorConnectGraphicsItem* item);

// QGraphicsItem interface
protected:
    void
    mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void
    mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void
    mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void
    hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    void
    hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    void
    calculatePath();

    void
    deleteThis();

private:
    QPointF _beginPoint;
    QPointF _endPoint;
    QPainterPath _linePath;
    PointValueType _pointValueType;
    VectorPointGraphicsItem* _from;
    VectorPointGraphicsItem* _to;
    QGraphicsScene* _scene;
};

#endif // VECTORCONNECTGRAPHICSITEM_HPP

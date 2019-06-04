#ifndef VECTORPOINTGRAPHICSITEM_HPP
#define VECTORPOINTGRAPHICSITEM_HPP

#include <QGraphicsObject>
#include "VectorConverterTypes.hpp"

class QGraphicsScene;

class VectorPointGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    VectorPointGraphicsItem( PointValueType pointValueType
                           , PointType pointType );

    // QGraphicsItem interface
public:
    QRectF
    boundingRect() const override;

    void
    paint( QPainter* painter
         , const QStyleOptionGraphicsItem* option
         , QWidget* widget ) override;

    PointType
    pointType();

    PointValueType
    pointValueType();

signals:
    void
    onTryCreateNewConnect(VectorPointGraphicsItem* sender);

protected:
    void
    mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void
    hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    void
    hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    PointValueType _pointValueType;
    PointType _pointType;
    QString _name;

};

#endif // VECTORPOINTGRAPHICSITEM_HPP

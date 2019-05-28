#include "VectorPointGraphicsItem.hpp"
#include <QPainter>
#include <QFontMetrics>
#include "VectorConverterStyle.hpp"

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>

#include "VectorConnectGraphicsItem.hpp"

VectorPointGraphicsItem::
VectorPointGraphicsItem( PointValueType pointValueType
                       , PointType pointType )
    : _pointValueType(pointValueType)
    , _pointType(pointType)
{
    switch ( pointValueType ) {
        case PointValueType::Red:    _name = "R"; break;
        case PointValueType::Green:  _name = "G"; break;
        case PointValueType::Blue:   _name = "B"; break;
        case PointValueType::Alpha:  _name = "A"; break;
    }

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    //setCacheMode( QGraphicsItem::DeviceCoordinateCache );

    setZValue(0);

    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(Qt::black);
    effect->setOffset({0,0});
    effect->setBlurRadius(8);
    setGraphicsEffect(effect);
}


QRectF
VectorPointGraphicsItem::
boundingRect() const
{
    switch ( _pointType ) {
        case PointType::Input: return QRectF(-36, -10, 52, 20);
        case PointType::Output: return QRectF(-16, -10, 52, 20);
    }
}

void
VectorPointGraphicsItem::
paint( QPainter* painter
     , const QStyleOptionGraphicsItem* option
     , QWidget* )
{
    painter->setClipRect(option->exposedRect);

    painter->setRenderHint(QPainter::RenderHint::Antialiasing, true);
    painter->setFont(VectorConverterStyle::pointFont());
    painter->setBrush(VectorConverterStyle::pointBrush(_pointValueType));
    painter->setPen(VectorConverterStyle::pointPen(_pointValueType));

    painter->drawEllipse(-8, -8, 16, 16);

    QFontMetrics fontMetrix(VectorConverterStyle::pointFont());
    qreal characterOffset = 20;
    qreal fontWidth = fontMetrix.width(_name);
    qreal fontPosY = fontMetrix.height() / 4;

    switch ( _pointType ) {
        case PointType::Input:
            painter->drawText( QPointF(-characterOffset - fontWidth, fontPosY)
                             , _name );
        break;

        case PointType::Output:
            painter->drawText( QPointF(characterOffset, fontPosY)
                             , _name );
        break;
    }
}


PointType
VectorPointGraphicsItem::
pointType()
{
    return _pointType;
}


PointValueType
VectorPointGraphicsItem::
pointValueType()
{
    return _pointValueType;
}


void
VectorPointGraphicsItem::
mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);

    if ( _pointType != PointType::Input ) {
        event->ignore();
        return;
    }

    emit onTryCreateNewConnect(this);
    event->accept();
}


void
VectorPointGraphicsItem::
hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    auto effect = dynamic_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    effect->setBlurRadius(16);
    effect->setColor(VectorConverterStyle::pointColor(_pointValueType));
}


void
VectorPointGraphicsItem::
hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    auto effect = dynamic_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    effect->setBlurRadius(8);
    effect->setColor(Qt::black);
}

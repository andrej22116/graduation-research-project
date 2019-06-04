#include "VectorConverterWidget.hpp"
#include "VectorConverterScene.hpp"



VectorConverterWidget::
VectorConverterWidget( unsigned char points
                     , QWidget* parent )
    : QGraphicsView(parent)
{
    setScene(new VectorConverterScene(points, this));
    setStyleSheet("background-color: transparent; border: 0 solid black;");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);

    auto size = sizeHint();
    size += {16, 16};
    setFixedSize(size);
}


QJsonObject
VectorConverterWidget::
save() const
{
    return dynamic_cast<VectorConverterScene*>(scene())->save();
}

void
VectorConverterWidget::
restore(const QJsonObject& obj)
{
    dynamic_cast<VectorConverterScene*>(scene())->restore(obj);
}

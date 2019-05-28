#include "VectorConverterWidget.hpp"
#include "VectorConverterScene.hpp"



VectorConverterWidget::
VectorConverterWidget( unsigned char points
                     , QWidget* parent )
    : QGraphicsView(parent)
{
    setScene(new VectorConverterScene(points, this));
    setStyleSheet("background-color: transparent;");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);

    auto size = sizeHint();
    size += {16, 16};
    setFixedSize(size);
}

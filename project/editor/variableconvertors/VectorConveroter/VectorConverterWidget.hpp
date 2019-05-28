#ifndef VECTORCONVERTER_HPP
#define VECTORCONVERTER_HPP

#include <QGraphicsView>

class VectorConverterWidget : public QGraphicsView
{
public:
    VectorConverterWidget(unsigned char points = 4, QWidget* parent = nullptr);

    // QGraphicsView interface
protected:/*
    void
    mousePressEvent(QMouseEvent* event) override;

    void
    mouseReleaseEvent(QMouseEvent* event) override;

    void
    mouseMoveEvent(QMouseEvent* event) override;*/
};

#endif // VECTORCONVERTER_HPP

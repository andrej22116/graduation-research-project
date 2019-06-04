#ifndef VECTORCONVERTER_HPP
#define VECTORCONVERTER_HPP

#include <QGraphicsView>
#include <nodes/internal/Serializable.hpp>

class VectorConverterWidget : public QGraphicsView
                            , public QtNodes::Serializable
{
public:
    VectorConverterWidget(unsigned char points = 4, QWidget* parent = nullptr);

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;
};

#endif // VECTORCONVERTER_HPP

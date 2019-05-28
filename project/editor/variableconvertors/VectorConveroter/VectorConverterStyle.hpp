#ifndef VECTORCONVERTERSTYLE_HPP
#define VECTORCONVERTERSTYLE_HPP

#include "VectorConverterTypes.hpp"

class QBrush;
class QColor;
class QPen;
class QFont;

class VectorConverterStyle
{
public:
    static const QBrush&
    pointBrush(PointValueType pointValueType);

    static const QColor&
    pointColor(PointValueType pointValueType);

    static const QPen&
    pointPen(PointValueType pointValueType);

    static const QFont&
    pointFont();
};

#endif // VECTORCONVERTERSTYLE_HPP

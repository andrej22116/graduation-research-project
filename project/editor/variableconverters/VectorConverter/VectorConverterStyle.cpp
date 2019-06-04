#include "VectorConverterStyle.hpp"
#include <QColor>
#include <QFont>
#include <QBrush>
#include <QPen>

const QBrush&
VectorConverterStyle::
pointBrush(PointValueType pointValueType)
{
    static QBrush redBrush      {{206, 41, 112}};
    static QBrush greenBrush    {{140, 206, 41}};
    static QBrush blueBrush     {{41, 143, 206}};
    static QBrush alphaBrush    {Qt::lightGray};

    switch ( pointValueType ) {
        case PointValueType::Red:    return redBrush;
        case PointValueType::Green:  return greenBrush;
        case PointValueType::Blue:   return blueBrush;
        case PointValueType::Alpha:  return alphaBrush;
    }
}

const QColor&
VectorConverterStyle::
pointColor(PointValueType pointValueType)
{
    static QColor redColor      {255, 48, 113};
    static QColor greenColor    {179, 255, 48};
    static QColor blueColor     {48, 189, 255};
    static QColor alphaColor    {Qt::white};

    switch ( pointValueType ) {
        case PointValueType::Red:    return redColor;
        case PointValueType::Green:  return greenColor;
        case PointValueType::Blue:   return blueColor;
        case PointValueType::Alpha:  return alphaColor;
    }
}

const QPen&
VectorConverterStyle::
pointPen(PointValueType pointValueType)
{
    static QPen redPen      {QBrush(pointColor(PointValueType::Red)), 4.0};
    static QPen greenPen    {QBrush(pointColor(PointValueType::Green)), 4.0};
    static QPen bluePen     {QBrush(pointColor(PointValueType::Blue)), 4.0};
    static QPen alphaPen    {QBrush(pointColor(PointValueType::Alpha)), 4.0};

    switch ( pointValueType ) {
        case PointValueType::Red:    return redPen;
        case PointValueType::Green:  return greenPen;
        case PointValueType::Blue:   return bluePen;
        case PointValueType::Alpha:  return alphaPen;
    }
}

const QFont&
VectorConverterStyle::
pointFont()
{
    static QFont font("Arial", 16, QFont::Bold);
    return font;
}

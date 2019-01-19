#include "DoubleData.hpp"

QtNodes::NodeDataType DoubleData::type() const
{
    return NodeDataType {"double", "Double"};
}

double DoubleData::number() const
{
    return _number;
}

QString DoubleData::numberAsText() const
{
    return QString::number(_number, 'f');
}

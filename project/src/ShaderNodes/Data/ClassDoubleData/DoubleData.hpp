#pragma once

#ifndef DOUBLE_DATA_HPP
#define DOUBLE_DATA_HPP


#include <nodes/NodeDataModel>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

class DoubleData : public NodeData
{
public:

  DoubleData() : _number(0.0) {}

  DoubleData(double const number) : _number(number) {}

  NodeDataType type() const override;

  double number() const;

  QString numberAsText() const;

private:

  double _number;
};


#endif

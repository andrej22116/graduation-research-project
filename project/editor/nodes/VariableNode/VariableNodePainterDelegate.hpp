#ifndef VARIABLENODEPAINTERDELEGATE_HPP
#define VARIABLENODEPAINTERDELEGATE_HPP

#include <nodes/NodePainterDelegate>

class VariableNodePainterDelegate : public QtNodes::NodePainterDelegate
{
public:
    ~VariableNodePainterDelegate() = default;

    // NodePainterDelegate interface
public:
    void paint( QPainter* painter
              , const QtNodes::NodeGeometry& geom
              , const QtNodes::NodeDataModel* model) override;
};

#endif // VARIABLENODEPAINTERDELEGATE_HPP

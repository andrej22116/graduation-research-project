#pragma once

#include <QtGui/QPainter>
#include "Export.hpp"

namespace QtNodes
{

class Node;
class NodeState;
class NodeGeometry;
class NodeGraphicsObject;
class NodeDataModel;
class FlowItemEntry;
class DataModelRegistry;

class NODE_EDITOR_PUBLIC NodePainter
{
public:

  NodePainter();

public:

  static
  void
  paint(QPainter* painter,
        Node& node,
        DataModelRegistry& registry);

  static
  void
  drawNodeRect(QPainter* painter,
               NodeGeometry const& geom,
               NodeDataModel const* model,
               bool graphicsObjectIsSelected = false);

  static
  void
  drawModelName(QPainter* painter,
                NodeGeometry const& geom,
                NodeState const& state,
                NodeDataModel const * model);

  static
  void
  drawEntryLabels(QPainter* painter,
                  NodeGeometry const& geom,
                  NodeState const& state,
                  NodeDataModel const * model);

  static
  void
  drawConnectionPoints(QPainter* painter,
                       NodeGeometry const& geom,
                       NodeState const& state,
                       NodeDataModel const * model,
                       DataModelRegistry const& registry);

  static
  void
  drawFilledConnectionPoints(QPainter* painter,
                             NodeGeometry const& geom,
                             NodeState const& state,
                             NodeDataModel const * model);

  static
  void
  drawResizeRect(QPainter* painter,
                 NodeGeometry const& geom,
                 NodeDataModel const * model);

  static
  void
  drawValidationRect(QPainter * painter,
                     NodeGeometry const & geom,
                     NodeDataModel const * model,
                     bool graphicsObjectIsSelected = false);
};
}

#include "NodeState.hpp"

#include "NodeDataModel.hpp"

#include "Connection.hpp"

#include <algorithm>

using QtNodes::NodeState;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::Connection;

NodeState::
NodeState(std::unique_ptr<NodeDataModel> const &model)
  : _inConnections(model->nPorts(PortType::In))
  , _outConnections(model->nPorts(PortType::Out))
  , _reaction(NOT_REACTING)
  , _reactingPortType(PortType::None)
  , _resizing(false)
  , _dataModel(model)
{}


void
NodeState::
updateModel()
{
    /// Remove or Add IN ports
    auto nPortsIn = _dataModel->nPorts(PortType::In);
    if ( nPortsIn < _inConnections.size() ) {
        std::for_each( _inConnections.begin() + nPortsIn
                     , _inConnections.end()
                     , [](ConnectionPtrSet& ptrSet) {
            std::for_each( ptrSet.begin()
                         , ptrSet.end()
                         , [](std::pair<QUuid, Connection*> connection) {
                connection.second->removeFromNodes();
            });
        });

        _inConnections.erase(_inConnections.begin() + nPortsIn);
    }
    else if ( nPortsIn > _inConnections.size() ) {
        _inConnections.resize(nPortsIn);
    }

    /// Remove or Add OUT ports
    auto nPortsOut = _dataModel->nPorts(PortType::Out);
    if ( nPortsOut < _outConnections.size() ) {
        std::for_each( _outConnections.begin() + nPortsOut
                     , _outConnections.end()
                     , [](ConnectionPtrSet& ptrSet) {
            std::for_each( ptrSet.begin()
                         , ptrSet.end()
                         , [](std::pair<QUuid, Connection*> connection) {
                connection.second->removeFromNodes();
            });
        });

        _outConnections.erase(_outConnections.begin() + nPortsOut);
    }
    else if ( nPortsOut > _outConnections.size() ) {
        _outConnections.resize(nPortsOut);
    }

    /// @todo Add test on invalid in/out ports!
}


std::vector<NodeState::ConnectionPtrSet> const &
NodeState::
getEntries(PortType portType) const
{
  if (portType == PortType::In)
    return _inConnections;
  else
    return _outConnections;
}


std::vector<NodeState::ConnectionPtrSet> &
NodeState::
getEntries(PortType portType)
{
  if (portType == PortType::In)
    return _inConnections;
  else
    return _outConnections;
}


NodeState::ConnectionPtrSet
NodeState::
connections(PortType portType, PortIndex portIndex) const
{
  auto const &connections = getEntries(portType);

  return connections[portIndex];
}


void
NodeState::
setConnection(PortType portType,
              PortIndex portIndex,
              Connection& connection)
{
  auto &connections = getEntries(portType);

  connections.at(portIndex).insert(std::make_pair(connection.id(),
                                               &connection));
}


void
NodeState::
eraseConnection(PortType portType,
                PortIndex portIndex,
                QUuid id)
{
  getEntries(portType)[portIndex].erase(id);
}


NodeState::ReactToConnectionState
NodeState::
reaction() const
{
  return _reaction;
}


PortType
NodeState::
reactingPortType() const
{
  return _reactingPortType;
}


NodeDataType
NodeState::
reactingDataType() const
{
  return _reactingDataType;
}


void
NodeState::
setReaction(ReactToConnectionState reaction,
            PortType reactingPortType,
            NodeDataType reactingDataType)
{
  _reaction = reaction;

  _reactingPortType = reactingPortType;

  _reactingDataType = std::move(reactingDataType);
}


bool
NodeState::
isReacting() const
{
  return _reaction == REACTING;
}


void
NodeState::
setResizing(bool resizing)
{
  _resizing = resizing;
}


bool
NodeState::
resizing() const
{
  return _resizing;
}

#ifndef VARIABLESCONTROLLER_HPP
#define VARIABLESCONTROLLER_HPP

#include <memory>
#include <functional>
#include <QHash>

/*
namespace QtNodes {
    class NodeDataModel;
    class FlowView;
    class FlowScene;
}

class QWidget;

using QtNodes::NodeDataModel;
using QtNodes::FlowView;
using QtNodes::FlowScene;*/

class VariableDataModel;

class VariablesController
{
public:
    VariablesController();



    /*
    using NodeDataModelFactoryType = std::unique_ptr<NodeDataModel>;
    using NodeDataModelFactory = std::function<NodeDataModelFactoryType()>;

    NodeDataModelFactory
    dataModelFactory();*/
/*
private:
    std::shared_ptr<QWidget> _widgetController;*/

    std::function<

private:
    QHash<QString, std::shared_ptr<VariableDataModel>> _variables;
};

#endif // VARIABLESCONTROLLER_HPP

#ifndef VARIABLESCONTROLLER_HPP
#define VARIABLESCONTROLLER_HPP

#include <memory>
#include <QHash>

#include <QObject>

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

class VariablesController : QObject
{
    Q_OBJECT

public:
    VariablesController();

    QStringList
    defaultVariablesNames();

    QStringList
    variablesNames();

    QStringList
    supportedVariablesTypes();

    QWidget*
    getVariableEditor(const QString& name);

signals:
    void
    variableControllerError(const QString& why);

public slots:
    void
    onCreateVariable(const QString& name);

    void
    onRenameVariable( const QString& oldName
                    , const QString& newName );

    void
    onRemoveVariable(const QString& name);

    void
    onChangeVariableDataModel( const QString& variableName
                             , const QString& dataModelName );

    void
    onAddDefaultVariableToScene( const QString& name
                               , const QString& typeName
                               , std::shared_ptr<VariableDataModel> data);

    void
    onAddVariableToScene(const QString& name);

private:
    QHash<QString, std::shared_ptr<VariableDataModel>> _defaultVariables;
    QHash<QString, std::shared_ptr<VariableDataModel>> _variables;
    QHash<QString, QString> _variablesTypes;
};

#endif // VARIABLESCONTROLLER_HPP

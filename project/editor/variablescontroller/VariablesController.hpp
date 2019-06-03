#ifndef VARIABLESCONTROLLER_HPP
#define VARIABLESCONTROLLER_HPP

#include <memory>
#include <QHash>

#include <QObject>
#include "nodes/internal/Serializable.hpp"

namespace QtNodes {
    class Node;
    class NodeDataModel;
    class FlowView;
}

class VariableDataModel;
class EditorGraphicsScene;

class VariablesController : public QObject
                          , public QtNodes::Serializable
{
    Q_OBJECT

public:
    using FlowViewPtr = std::shared_ptr<QtNodes::FlowView>;
    using EditorGraphicsScenePtr = std::shared_ptr<EditorGraphicsScene>;

    VariablesController( FlowViewPtr view
                       , EditorGraphicsScenePtr scene );

    QStringList
    defaultVariablesNames();

    QStringList
    variablesNames();

    const QStringList&
    supportedVariablesTypes();

    QWidget*
    getVariableEditor(const QString& name);

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

signals:
    void
    variableControllerError(const QString& why);

    void
    variableChangeName( const QString& oldName
                      , const QString& newName );

    void
    variableSelected( std::shared_ptr<VariableDataModel> variableDataModel
                    , const QString& dataTypeName );

public slots:
    void
    onSelectVariable(const QString& name);

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

    void
    onRemoveVariableNodeFromScene(QtNodes::Node& node);

private:
    QHash<QString, std::shared_ptr<VariableDataModel>> _defaultVariables;
    QHash<QString, std::shared_ptr<VariableDataModel>> _variables;
    QHash<QString, QString> _variablesTypes;
    QHash<QString, QSet<QUuid>> _variablesNodesIds;
    QHash<QUuid, QString> _nodesIdAssociate;
    QHash<QUuid, QtNodes::NodeDataModel*> _nodesDataModels;
    QStringList _supportedVariablesTypes;
    FlowViewPtr _view;
    EditorGraphicsScenePtr _scene;
};

#endif // VARIABLESCONTROLLER_HPP

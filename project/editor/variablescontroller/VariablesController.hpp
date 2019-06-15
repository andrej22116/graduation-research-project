#ifndef VARIABLESCONTROLLER_HPP
#define VARIABLESCONTROLLER_HPP

#include <memory>
#include <functional>
#include <QHash>
#include <QSet>

#include <QObject>

namespace QtNodes {
    class Node;
    class NodeDataModel;
    class FlowView;
}

class VariableDataModel;
class EditorGraphicsScene;
class VariableNode;

class VariablesController : public QObject
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


public:
    QJsonArray
    save() const;

    void
    restore(const QJsonArray&);

signals:
    void
    variableControllerError(const QString& why);

    void
    variableSelected( std::shared_ptr<VariableDataModel> variableDataModel
                    , const QString& dataTypeName );

    void
    createdNewUserVariable(const QString& name);

    void
    createdNewDefaultVariable(const QString& name);

    void
    renamedUserVariable( const QString& oldName
                       , const QString& newName );

    void
    renamedDefaultVariable( const QString& oldName
                          , const QString& newName );

    void
    removedUserVariable(const QString& name);

    void
    removedDefaultVariable(const QString& name);

    void
    variableValueChanged(const QString& name);

public slots:
    void
    onSelectVariable(const QString& name);

    void
    onChangeVariableDataModel( const QString& variableName
                             , const QString& dataModelName );

    void
    addVariableToScene(const QString& name);

    void
    onRemoveVariableNodeFromScene(QtNodes::Node& node);

    bool
    createUserVariable(const QString& name);

    void
    createUserVariableWithSignal(const QString& name);

    bool
    renameUserVariable( const QString& oldName
                      , const QString& newName );

    void
    renameUserVariableWithSignal( const QString& oldName
                                , const QString& newName );

    bool
    removeUserVariable(const QString& name);

    void
    removeUserVariableWithSignal(const QString& name);

private:
    bool
    createDefaultVariable( const QString& name
                         , const QString& typeName );

    void
    createDefaultVariableWithSignal( const QString& name
                                   , const QString& typeName );

    bool
    renameDefaultVariable( const QString& oldName
                         , const QString& newName );

    void
    renameDefaultVariableWithSignal( const QString& oldName
                                   , const QString& newName );

    bool
    removeDefaultVariable(const QString& name);

    void
    removeDefaultVariableWithSignal(const QString& name);

    bool
    variableNameExists(const QString& name);

private:
    using DefaultVariablesSet = QSet<QString>;
    using VariablesModelsHash = QHash< QString
                                     , std::shared_ptr<VariableDataModel> >;
    using VariablesTypeNamesHash = QHash<QString, QString>;
    using VariablesNodesInSceneHash = QHash<QString, QSet<QUuid>>;
    using VariablesNodesAssociacionHash = QHash<QUuid, QString>;
    using VariablesNodesDataModelsHash = QHash<QUuid, QtNodes::NodeDataModel*>;

    void
    renameVariable( const QString& oldName
                  , const QString& newName);

    void
    removeVariable( const QString& name);

private:

    DefaultVariablesSet _defaultVariables;
    VariablesModelsHash _variables;
    VariablesTypeNamesHash _variablesTypes;
    VariablesNodesInSceneHash _variablesNodesIds;
    VariablesNodesAssociacionHash _nodesIdAssociate;
    VariablesNodesDataModelsHash _nodesDataModels;
    QStringList _supportedVariablesTypes;
    FlowViewPtr _view;
    EditorGraphicsScenePtr _scene;
};

#endif // VARIABLESCONTROLLER_HPP

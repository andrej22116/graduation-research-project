#ifndef DEFAULTGLSLCOMPILER_HPP
#define DEFAULTGLSLCOMPILER_HPP

//#include <ICompiler.hpp>
#include "../ICompiler.hpp"

#include <QHash>
#include <QSet>
#include <QTextStream>
#include <memory>
#include <functional>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QUuid>

class DefaultGlslCompiler : public ICompiler
{
    Q_OBJECT

    // ICompiler interface
public:
    DefaultGlslCompiler();
    ~DefaultGlslCompiler() override {}

    void
    compile(std::shared_ptr<QJsonObject> sources) override;

public slots:
    void
    nextStep() override;

private:
    void
    writeHeader();

    void
    hashVariables();

    void
    hashNodes();

    void
    hashDependecis();

    void
    calculateNodesWeight();

    void
    sortingNodesByWeight();

    void
    generateSources();

    void
    buildResult();

    void
    complete();

private:
    void
    handleVariableNode( const QUuid& id
                      , const QJsonObject& obj );

    void
    handleConstVariableNode( const QUuid& id
                           , const QJsonObject& obj );

    void
    handleFunctionalNode( const QUuid& id
                        , const QJsonObject& obj );

    void
    handleConverterNode( const QUuid& id
                       , const QJsonObject& obj );

private:
    QHash<QString, QUuid> _variablesValueSources;
    QSet<QString> _variablesInitializations;
    QHash<QString, QString> _reservedVariablesNames;

    QHash<QString, QString> _dataTypeAssociation;
    QHash<QString, std::function<QString(const QJsonValue&)>> _constConvertors;

    std::unique_ptr<QTextStream> _textStream;

    std::shared_ptr<QJsonObject> _sources;
    double _procent;
    double _procentScaleSpeed;

private:
    using NodeTypeHandler = std::function<void( DefaultGlslCompiler*
                                              , const QUuid&
                                              , const QJsonObject& )>;
    QHash<QString, NodeTypeHandler> _nodesTypesHandlers;

    QHash<QUuid, QJsonObject> _models;
    QHash<QUuid, QString> _constants;
    QHash<QUuid, QString> _functions;
    QHash<QUuid, QHash<int, QUuid>> _dependencis;
    QHash<QUuid, int> _nodesWeights;
    QVector<QUuid> _sortedNodesIds;
    QHash<QUuid, QString> _nodesStringValuesForDeploy;
    QVector<QString> _finalNodesStringValues;

    std::function<void(DefaultGlslCompiler*)> _currentFunction;
    std::shared_ptr<QJsonArray> _array;
    QJsonArray::iterator _arrayIterator;

    int _f_res_index = 1;
};

#endif // DEFAULTGLSLCOMPILER_HPP

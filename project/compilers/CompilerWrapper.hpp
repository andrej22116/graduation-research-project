#ifndef COMPILEWRAPPER_HPP
#define COMPILEWRAPPER_HPP

#include <QObject>
#include "ICompiler.hpp"

class CompilerWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CompilerWrapper(QObject *parent = nullptr);

    void
    setCompiler(std::shared_ptr<ICompiler> compiler);

    void
    setSources(std::shared_ptr<QJsonObject> sources);

public slots:
    void
    compile();

signals:
    void
    nextStep();

    void
    compileComplete(const QString& fragmentShaderText);

    void
    compileChangeState( int state
                      , const QString& stateText );

    void
    compileError(const QString& what);

private slots:
    void
    onNextStep();

    void
    onCompileComplete(const QString&);

private:
    bool _compiling;
    std::shared_ptr<ICompiler> _compiler;
    std::shared_ptr<QJsonObject> _sources;
};

#endif // COMPILEWRAPPER_HPP

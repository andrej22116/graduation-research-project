#ifndef COMPILLERCONTROLLER_HPP
#define COMPILLERCONTROLLER_HPP

#include <QObject>
#include <QHash>
#include <memory>

class QJsonObject;
class QThread;
class ICompiler;
class CompilerWrapper;

class CompilerController : public QObject
{
    Q_OBJECT

public:
    CompilerController();

    const QStringList&
    supportedCompilers() const;

signals:
    void
    startCompile();

    void
    compileComplete(const QString& fragmentShaderText);

    void
    compileChangeState( int state
                      , const QString& stateText );

    void
    compileError(const QString& what);

public slots:
    void
    compile( const QString& compilerName
           , std::shared_ptr<QJsonObject> sources );

    void
    stopCompile();

private slots:
    void
    onCompleteCompile(const QString& fragmentShaderText);

private:
    void
    setConnections();

private:
    std::shared_ptr<QThread> _compileThread;
    std::shared_ptr<CompilerWrapper> _compileWrapper;

private:
    QStringList _supportedCompilers;
    QHash<QString, std::shared_ptr<ICompiler>> _compilers;
};

#endif // COMPILLERCONTROLLER_HPP

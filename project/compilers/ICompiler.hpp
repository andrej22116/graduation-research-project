#ifndef ICOMPILER_HPP
#define ICOMPILER_HPP

#include <QObject>
#include <memory>

class QJsonObject;

class ICompiler : public QObject
{
    Q_OBJECT

public:
    virtual ~ICompiler() {}

    virtual void
    compile(std::shared_ptr<QJsonObject> sources) = 0;

public slots:
    virtual void
    nextStep() = 0;

signals:
    void
    compileComplete(const QString& fragmentShaderText);

    void
    compileChangeState( int state
                      , const QString& stateText );

    void
    compileError(const QString& what);

};

//Q_DECLARE_INTERFACE(ICompiler, "ICompiler")

#endif // ICOMPILER_HPP

#include "CompilerController.hpp"
#include <QThread>

#include "CompilerWrapper.hpp"
#include "DefaultGlslCompiler/DefaultGlslCompiler.hpp"

CompilerController::
CompilerController()
    : _compileThread(new QThread(this))
    , _compileWrapper(new CompilerWrapper())
{
    _compileWrapper->moveToThread(_compileThread.get());

    setConnections();
}


const QStringList&
CompilerController::
supportedCompilers() const
{
    return _supportedCompilers;
}


void
CompilerController::
compile( const QString& /*compilerName*/
       , std::shared_ptr<QJsonObject> sources )
{
    auto compiller = std::make_shared<DefaultGlslCompiler>();
    auto compillerCast = std::static_pointer_cast<ICompiler>(compiller);
    _compileWrapper->setCompiler(compillerCast);
    _compileWrapper->setSources(sources);

    _compileThread->start();
    emit startCompile();
}


void
CompilerController::
stopCompile()
{
    _compileThread->quit();
}


void
CompilerController::
onCompleteCompile(const QString& fragmentShaderText)
{
    emit compileComplete(fragmentShaderText);
    stopCompile();
}


void
CompilerController::
setConnections()
{
    connect( this
           , &CompilerController::startCompile
           , _compileWrapper.get()
           , &CompilerWrapper::compile );

    connect( _compileWrapper.get()
           , &CompilerWrapper::compileComplete
           , this
           , &CompilerController::onCompleteCompile
           , Qt::UniqueConnection );

    connect( _compileWrapper.get()
           , &CompilerWrapper::compileChangeState
           , this
           , &CompilerController::compileChangeState
           , Qt::UniqueConnection );

    connect( _compileWrapper.get()
           , &CompilerWrapper::compileError
           , this
           , &CompilerController::compileError
           , Qt::UniqueConnection );
}

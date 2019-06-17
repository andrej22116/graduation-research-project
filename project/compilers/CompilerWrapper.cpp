#include "CompilerWrapper.hpp"

CompilerWrapper::
CompilerWrapper(QObject *parent)
    : QObject(parent)
    , _compiling(false)
    , _compiler(nullptr)
    , _sources(nullptr)
{
    connect( this
           , &CompilerWrapper::nextStep
           , this
           , &CompilerWrapper::onNextStep
           , Qt::ConnectionType::QueuedConnection );
}


void
CompilerWrapper::
setCompiler(std::shared_ptr<ICompiler> compiler)
{
    _compiler = compiler;
    if ( !_compiler ) {
        return;
    }

    connect( _compiler.get()
           , &ICompiler::compileComplete
           , this
           , &CompilerWrapper::onCompileComplete
           , Qt::UniqueConnection );

    connect( _compiler.get()
           , &ICompiler::compileComplete
           , this
           , &CompilerWrapper::compileComplete
           , Qt::UniqueConnection );

    connect( _compiler.get()
           , &ICompiler::compileChangeState
           , this
           , &CompilerWrapper::compileChangeState
           , Qt::UniqueConnection );

    connect( _compiler.get()
           , &ICompiler::compileError
           , this
           , &CompilerWrapper::compileError
           , Qt::UniqueConnection );
}


void
CompilerWrapper::
setSources(std::shared_ptr<QJsonObject> sources)
{
    /*
    if ( !_compiler ) {
        emit compileError("[SET USER SOURCE] Compiller is not installed.");
        return;
    }
    */
    _sources = sources;
}


void
CompilerWrapper::
compile()
{
    if ( !_compiler ) {
        emit compileError("[SET USER SOURCE] Compiller is not installed.");
        return;
    }
    _compiling = true;

    _compiler->compile(_sources);
    emit nextStep();
}


void
CompilerWrapper::
onNextStep()
{
    _compiler->nextStep();

    if ( _compiling ) {
        emit nextStep();
    }
}


void
CompilerWrapper::
onCompileComplete(const QString&)
{
    _compiling = false;
}

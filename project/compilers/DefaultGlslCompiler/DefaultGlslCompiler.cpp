#include "DefaultGlslCompiler.hpp"


void
DefaultGlslCompiler::
compile(std::shared_ptr<QJsonObject> sources)
{
    //auto& sourceObj = *sources;
    _sources = sources;
}


void
DefaultGlslCompiler::
nextStep()
{
    if ( i <= 10 ) {
        emit compileChangeState(i * 10, "Compiling...");
        ++i;
    }
    else {
        emit compileComplete("Lol");
    }
}

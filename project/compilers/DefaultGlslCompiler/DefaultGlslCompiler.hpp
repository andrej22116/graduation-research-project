#ifndef DEFAULTGLSLCOMPILER_HPP
#define DEFAULTGLSLCOMPILER_HPP

//#include <ICompiler.hpp>
#include "../ICompiler.hpp"

class DefaultGlslCompiler : public ICompiler
{
    Q_OBJECT

    // ICompiler interface
public:
    ~DefaultGlslCompiler() override {}

    void
    compile(std::shared_ptr<QJsonObject> sources) override;

public slots:
    void
    nextStep() override;

private:
    std::shared_ptr<QJsonObject> _sources;
    int i = 0;
};

#endif // DEFAULTGLSLCOMPILER_HPP

#ifndef TARGETSCENERENDERERFACTORY_HPP
#define TARGETSCENERENDERERFACTORY_HPP

#include <string>
#include <memory>

class ITargetSceneRenderer;

class TargetSceneRendererFactory
{
    TargetSceneRendererFactory() = default;
    ~TargetSceneRendererFactory() = default;

public:
    static std::shared_ptr<ITargetSceneRenderer> create(const std::string& name);
};

#endif // TARGETSCENERENDERERFACTORY_HPP

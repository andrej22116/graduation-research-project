#ifndef TARGETSCENERENDERERFACTORY_HPP
#define TARGETSCENERENDERERFACTORY_HPP

#include <memory>

class ITargetSceneRenderer;

class TargetSceneRendererFactory
{
    TargetSceneRendererFactory() = default;
    ~TargetSceneRendererFactory() = default;

public:
    static std::shared_ptr<ITargetSceneRenderer> create(std::string name);
};

#endif // TARGETSCENERENDERERFACTORY_HPP

#include "VisualizerController.hpp"
#include "TargetSceneWrapperWidget.hpp"
#include "OpenGLScene.hpp"

VisualizerController::
VisualizerController(QObject *parent)
    : QObject(parent)
{
    _wrapperWidget = std::make_shared<TargetSceneWrapperWidget>();
    _wrapperWidget->setTargetSceneRenderer(
                std::make_shared<OpenGLScene>(_wrapperWidget.get()));
}

QWidget*
VisualizerController::
widget()
{
    return _wrapperWidget.get();
}

void
VisualizerController::
updateSupportedDevicesList()
{

}

const QStringList&
VisualizerController::
supportedDevicesList() const
{
    return _supportedDevices;
}

void
VisualizerController::
setVisualizer(const QString& /*visualizerName*/)
{

}

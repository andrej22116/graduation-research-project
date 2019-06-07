#ifndef VISUALIZERCONTROLLER_HPP
#define VISUALIZERCONTROLLER_HPP

#include <QObject>
#include <memory>

class TargetSceneWrapperWidget;

class VisualizerController : public QObject
{
    Q_OBJECT

public:
    explicit
    VisualizerController(QObject *parent = nullptr);

    QWidget*
    widget();

    void updateSupportedDevicesList();

    const QStringList&
    supportedDevicesList() const;

    void
    setVisualizer(const QString& visualizerName = "");

private:
    std::shared_ptr<TargetSceneWrapperWidget> _wrapperWidget;
    QStringList _supportedDevices;
};

#endif // VISUALIZERCONTROLLER_HPP

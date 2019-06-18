#ifndef VISUALIZERCONTROLLER_HPP
#define VISUALIZERCONTROLLER_HPP

#include <QObject>
#include <memory>

class TargetSceneWrapperWidget;

#if defined(SHARED_LIBRARY)
#  define VISUALIZER_EXPORT Q_DECL_EXPORT
#else
#  define VISUALIZER_EXPORT Q_DECL_IMPORT
#endif

class VISUALIZER_EXPORT VisualizerController : public QObject
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

public slots:
    void
    setFragmentShaderText(const QString& text);

private:
    std::shared_ptr<TargetSceneWrapperWidget> _wrapperWidget;
    QStringList _supportedDevices;
};

#endif // VISUALIZERCONTROLLER_HPP

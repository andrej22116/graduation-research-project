#ifndef TARGETSCENEWRAPPERWIDGET_HPP
#define TARGETSCENEWRAPPERWIDGET_HPP

#include <QDockWidget>
#include <memory>

class ITargetSceneRenderer;

/**
 * @brief The TargetSceneWrapperWidget class contain scene renderer widget
 * and also adds additional functionality
 */
class TargetSceneWrapperWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TargetSceneWrapperWidget(QWidget* parent = nullptr);

    TargetSceneWrapperWidget( std::shared_ptr<ITargetSceneRenderer> targetSceneRenderer
                            , QWidget* parent = nullptr );

    /// Set target scene renderer to this wrapper;
    void setTargetSceneRenderer(std::shared_ptr<ITargetSceneRenderer> targetSceneRenderer);

    /// Return current target scene renderer
    std::shared_ptr<ITargetSceneRenderer> targetSceneRenderer();

    /// Set object from file to the target scene
    void setTargetObject(const QString& pathToObject);

private slots:
    /// Set object from selected (in dialog) file to the target scene
    void setTargetObject();

private:
    void createCentralWidget();

private:
    std::shared_ptr<ITargetSceneRenderer> _targetSceneRenderer;
    QWidget* centralWidget;
};

#endif // TARGETSCENEWRAPPERWIDGET_HPP

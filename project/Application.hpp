#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QMainWindow>
#include <memory>

class WelcomeWindowDialog;
class EditorController;
class VisualizerController;
class CompilerController;

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit
    Application( QApplication& application
               , QWidget* parent = nullptr );

    void
    startProject(const QString& projectPath);

    void
    startWelcomeWindow();

signals:

private slots:
    void
    onCreateEditorDockWidget();

    void
    onCreateEditorVariablesDockWidget();

    void
    onCreateEditorNodesStoreDockWidget();

    void
    onCreateVisualizerDockWidget();

private slots:
    void
    onExit();

    void
    onCreateSolution( const QString& solutionPath
                    , const QString& sulutionName
                    , bool needCreateFolder
                    , const QJsonObject& solutionSettings  );

    void
    onOpenSolution(const QString& solutionPath);

    void
    onSaveSolution();

    void
    onExportProject();

private:
    void
    createMenu();

private:
    QApplication& _application;
    QString _solutionPath;

    std::shared_ptr<WelcomeWindowDialog> _welcomWindowDialog;
    std::shared_ptr<EditorController> _editorController;
    std::shared_ptr<VisualizerController> _visualizerController;
    std::shared_ptr<CompilerController> _compilerController;

    QDockWidget* _editorWidget;
    QDockWidget* _variablesWidget;
    QDockWidget* _nodesWidget;
    QDockWidget* _visualizerWidget;
};

#endif // APPLICATION_HPP

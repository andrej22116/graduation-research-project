#include "Application.hpp"
#include "dialogs/WelcomeWindowDialog/WelcomeWindowDialog.hpp"
#include <QApplication>

#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>

#include <editor/EditorController.hpp>
#include <visualizers/VisualizerController.hpp>
#include <compilers/CompilerController.hpp>
#include <QJsonObject>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Application::
Application( QApplication& application
           , QWidget *parent )
    : QMainWindow(parent)
    , _application(application)
    , _welcomWindowDialog(new WelcomeWindowDialog())
    , _editorController(new EditorController(this))
    , _visualizerController(new VisualizerController(this))
    , _compilerController(new CompilerController(this))
    , _editorWidget(new QDockWidget("Shader node editor", this))
    , _variablesWidget(new QDockWidget("Variables", this))
    , _nodesWidget(new QDockWidget("Nodes store", this))
    , _visualizerWidget(new QDockWidget("Vizualizer", this))
{
    setStyleSheet("QWidget{background-color: rgb(60, 60, 65); color: white;}");


    _variablesWidget->close();
    _visualizerWidget->close();

    connect( _welcomWindowDialog.get()
           , &WelcomeWindowDialog::exit
           , this
           , &Application::onExit );

    connect( _welcomWindowDialog.get()
           , &WelcomeWindowDialog::openSolution
           , this
           , &Application::onOpenSolution );

    connect( _welcomWindowDialog.get()
           , &WelcomeWindowDialog::createSolution
           , this
           , &Application::onCreateSolution );

    //setDockNestingEnabled(true);
    setDockOptions( QMainWindow::AllowTabbedDocks
                  | QMainWindow::AllowNestedDocks
                  | QMainWindow::VerticalTabs
                  | QMainWindow::GroupedDragging );

    _editorWidget->setWidget(_editorController->editor());
    _variablesWidget->setWidget(_editorController->variables());
    _nodesWidget->setWidget(_editorController->nodesStore());
    _visualizerWidget->setWidget(_visualizerController->widget());

    _nodesWidget->widget()->resize(_nodesWidget->widget()->sizeHint());
    _nodesWidget->resize(_nodesWidget->widget()->sizeHint());

    createMenu();

    connect( _editorController.get()
           , &EditorController::compile
           , _compilerController.get()
           , [this](std::shared_ptr<QJsonObject> sources){
        _compilerController->compile("", sources);
    });

    connect( _compilerController.get()
           , &CompilerController::compileComplete
           , _visualizerController.get()
           , &VisualizerController::setFragmentShaderText );

    auto args = _application.arguments();
    if ( args.size() == 2 ) {
        startProject(args[1]);
    }
    else {
        startWelcomeWindow();
    }
}


void
Application::
startProject(const QString& projectPath)
{
    _solutionPath = projectPath;
    this->showMaximized();
    _welcomWindowDialog->hide();

    onCreateEditorDockWidget();
    onCreateVisualizerDockWidget();
    onCreateEditorVariablesDockWidget();
    onCreateEditorNodesStoreDockWidget();

    _editorController->restore(projectPath);

    //_visualizer;
}


void
Application::
startWelcomeWindow()
{
    this->showMaximized();
    this->hide();
    _welcomWindowDialog->show();
}


void Application::onExit()
{
    _application.exit();
}


void
Application::
onCreateSolution( const QString& solutionPath
                , const QString& solutionName
                , bool needCreateFolder
                , const QJsonObject&  /*solutionSettings*/ )
{

    auto path = QDir::cleanPath(solutionPath);
    if ( needCreateFolder ) {
        if ( QDir(path).mkdir(solutionName) ) {
            path += "/" + solutionName;
            path = QDir::cleanPath(path);
        }
    }

    path += "/" + solutionName;

    if (!path.endsWith("sdsln", Qt::CaseInsensitive)) {
        path += ".sdsln";
    }

    QFile file(path);
    if ( !file.open(QFile::WriteOnly) ) {
        QMessageBox::critical( this
                             , "Error!"
                             , "Invalid project name!" );
        return;
    }

    QFile baseFile(":/WelcomWindowDialog/src/base.sdsln");
    if ( baseFile.open(QFile::ReadOnly) ) {
        auto data = baseFile.readAll();
        file.write(data);
        baseFile.close();
    }

    file.close();

    startProject(path);
}


void
Application::
onOpenSolution(const QString& solutionPath)
{
    startProject(solutionPath);
}


void
Application::
onCreateEditorDockWidget()
{
    _editorWidget->setFloating(false);
    _editorWidget->show();
    addDockWidget( Qt::DockWidgetArea::RightDockWidgetArea
                 , _editorWidget
                 , Qt::Orientation::Horizontal );
}


void
Application::
onCreateEditorVariablesDockWidget()
{
    _variablesWidget->setFloating(false);
    _variablesWidget->show();
    addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea
                 , _variablesWidget
                 , Qt::Orientation::Vertical );

    if ( _visualizerWidget->isVisible() ) {
        splitDockWidget( _visualizerWidget
                       , _variablesWidget
                       , Qt::Orientation::Horizontal );
    }
}


void
Application::
onCreateEditorNodesStoreDockWidget()
{
    _nodesWidget->setFloating(false);
    _nodesWidget->show();
    addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea
                 , _nodesWidget
                 , Qt::Orientation::Horizontal );
}


void
Application::
onCreateVisualizerDockWidget()
{
    _visualizerWidget->setFloating(false);
    _visualizerWidget->show();
    addDockWidget( Qt::RightDockWidgetArea
                 , _visualizerWidget
                 , Qt::Orientation::Vertical );

    if ( _editorWidget->isVisible() ) {
        splitDockWidget( _visualizerWidget
                       , _editorWidget
                       , Qt::Orientation::Vertical );
    }
}


void
Application::
onSaveSolution()
{   
    _editorController->save(_solutionPath);
}


void
Application::
onExportProject()
{
    auto json = _editorController->save();
    connect( _compilerController.get()
           , &CompilerController::compileComplete
           , this
           , &Application::onCompileComplete );

    auto&& jsonR = std::move(json);
    _compilerController->compile( ""
                                , std::make_shared<QJsonObject>(jsonR));
}


void
Application::
onCompileComplete(const QString& shaderText)
{
    disconnect( _compilerController.get()
              , &CompilerController::compileComplete
              , this
              , &Application::onCompileComplete );

    QString fileName =
      QFileDialog::getSaveFileName(nullptr,
                                   tr("Export project"),
                                   "",
                                   tr("Text (*.txt)"));

    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith("txt", Qt::CaseInsensitive)) {
            fileName += ".txt";
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << shaderText;
        }
    }
}


void
Application::
createMenu()
{
    auto menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

///////////////////////////////////////////////////////////////////////////////

    auto file = menuBar->addMenu("&File");

    auto create = file->addAction("Create project");
    create->setShortcut(QKeySequence("Ctrl+N"));

    auto open = file->addAction("Open project");
    open->setShortcut(QKeySequence("Ctrl+O"));

    auto save = file->addAction("Save project");
    connect( save
           , &QAction::triggered
           , this
           , &Application::onSaveSolution );
    save->setShortcut(QKeySequence("Ctrl+S"));

    /*auto saveAs = file->addAction("Save project as...");
    saveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));*/

    file->addSeparator();

    auto exportProj = file->addAction("Export to...");
    connect( exportProj
           , &QAction::triggered
           , this
           , &Application::onExportProject );

    file->addSeparator();

    auto exit = file->addAction("Exit");
    connect( exit
           , &QAction::triggered
           , this
           , &Application::onExit );
    exit->setShortcut({"Alt+F4"});

///////////////////////////////////////////////////////////////////////////////

    auto tools = menuBar->addMenu("&Tools");
    auto compile = tools->addAction("Compile");
    connect( compile
           , &QAction::triggered
           , _editorController.get()
           , &EditorController::onBeginCompiling );
    compile->setShortcut({"Ctrl+B"});

///////////////////////////////////////////////////////////////////////////////

    //auto edit = menuBar->addMenu("&Edit");
    auto window = menuBar->addMenu("&Window");

    auto openEditor = window->addAction("Editor window");
    connect( openEditor
           , &QAction::triggered
           , this
           , &Application::onCreateEditorDockWidget );
    openEditor->setShortcut({"Ctrl+Shift+E"});

    auto openVariables =  window->addAction("Variables window");
    connect( openVariables
           , &QAction::triggered
           , this
           , &Application::onCreateEditorVariablesDockWidget );
    openVariables->setShortcut({"Ctrl+Shift+V"});

    auto openNodesStore = window->addAction("Nodes store window");
    connect( openNodesStore
           , &QAction::triggered
           , this
           , &Application::onCreateEditorNodesStoreDockWidget );
    openNodesStore->setShortcut({"Ctrl+Shift+N"});

    auto openVisualizer = window->addAction("Visualizer window");
    connect( openVisualizer
           , &QAction::triggered
           , this
           , &Application::onCreateVisualizerDockWidget );
    openVisualizer->setShortcut({"Ctrl+Alt+V"});

    /*auto action = file.addAction( "&Create project"
                                , [](){}
                                , QKeySequence(Qt::Key_Control, Qt::Key_N));*/
}

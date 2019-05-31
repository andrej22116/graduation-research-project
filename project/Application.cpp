#include "Application.hpp"
#include "dialogs/WelcomeWindowDialog/WelcomeWindowDialog.hpp"
#include <QApplication>

#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>

#include <editor/EditorController.hpp>

Application::
Application( QApplication& application
           , QWidget *parent )
    : QMainWindow(parent)
    , _application(application)
    , _welcomWindowDialog(new WelcomeWindowDialog())
    , _editorController(new EditorController(this))
    , _visualizerController(nullptr)
    , _compillerController(nullptr)
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

    setDockNestingEnabled(true);
    setDockOptions( QMainWindow::AllowTabbedDocks
                  | QMainWindow::AllowNestedDocks
                  | QMainWindow::VerticalTabs
                  | QMainWindow::GroupedDragging );

    _editorWidget->setWidget(_editorController->editor());
    _variablesWidget->setWidget(_editorController->variables());
    _nodesWidget->setWidget(_editorController->nodesStore());

    createMenu();

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
    this->show();
    _welcomWindowDialog->hide();

    onCreateEditorDockWidget();
    onCreateEditorNodesStoreDockWidget();
}


void
Application::
startWelcomeWindow()
{
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
                , const QString& /*sulutionName*/
                , bool /*needCreateFolder*/
                , const QJsonObject&  /*solutionSettings*/ )
{
    startProject(solutionPath);
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
    addDockWidget( Qt::DockWidgetArea::RightDockWidgetArea
                 , _editorWidget
                 , Qt::Orientation::Horizontal );
}


void
Application::
onCreateEditorVariablesDockWidget()
{
    addDockWidget( Qt::DockWidgetArea::RightDockWidgetArea
                 , _variablesWidget
                 , Qt::Orientation::Vertical );
}


void
Application::
onCreateEditorNodesStoreDockWidget()
{
    addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea
                 , _nodesWidget
                 , Qt::Orientation::Horizontal );
}


void
Application::
onCreateVisualizerDockWidget()
{
    addDockWidget( Qt::DockWidgetArea::RightDockWidgetArea
                 , _visualizerWidget
                 , Qt::Orientation::Vertical );
}


void
Application::
onSaveSolution()
{

}

#include <QDebug>
void
Application::
createMenu()
{
    auto menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    auto file = menuBar->addMenu("&File");

    auto create = file->addAction("Create project");
    create->setShortcut(QKeySequence("Ctrl+N"));

    auto open = file->addAction("Open project");
    open->setShortcut(QKeySequence("Ctrl+O"));

    auto save = file->addAction("Save project");
    save->setShortcut(QKeySequence("Ctrl+S"));

    auto saveAs = file->addAction("Save project as...");
    saveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));

    file->addSeparator();

    auto exit = file->addAction("Exit");
    connect(exit, &QAction::triggered, this, &Application::onExit);
    exit->setShortcut({"Alt+F4"});

    //auto edit = menuBar->addMenu("&Edit");
    auto window = menuBar->addMenu("&Window");

    auto openEditor = window->addAction("Editor window");
    connect(openEditor, &QAction::triggered, this, &Application::onCreateEditorDockWidget);
    openEditor->setShortcut({"Ctrl+Shift+E"});

    auto openVariables =  window->addAction("Variables window");
    connect(openVariables, &QAction::triggered, this, &Application::onCreateEditorVariablesDockWidget);
    openVariables->setShortcut({"Ctrl+Shift+V"});

    auto openNodesStore = window->addAction("Nodes store window");
    connect(openNodesStore, &QAction::triggered, this, &Application::onCreateEditorNodesStoreDockWidget);
    openNodesStore->setShortcut({"Ctrl+Shift+N"});

    auto openVisualizer = window->addAction("Visualizer window");
    connect(openVisualizer, &QAction::triggered, this, &Application::onCreateVisualizerDockWidget);
    openVisualizer->setShortcut({"Ctrl+Alt+V"});

    /*auto action = file.addAction( "&Create project"
                                , [](){}
                                , QKeySequence(Qt::Key_Control, Qt::Key_N));*/
}

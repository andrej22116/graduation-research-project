#include "TargetSceneWrapperWidget.hpp"
#include "ITargetSceneRenderer.hpp"
#include "TargetObject.hpp"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

TargetSceneWrapperWidget::TargetSceneWrapperWidget(QWidget* parent) :
    QDockWidget(parent),
    centralWidget(nullptr)
{
    setAllowedAreas(Qt::AllDockWidgetAreas);
    createCentralWidget();
}

TargetSceneWrapperWidget::TargetSceneWrapperWidget( std::shared_ptr<ITargetSceneRenderer> targetSceneRenderer
                                                  , QWidget* parent ) :
    QDockWidget(parent),
    centralWidget(nullptr)
{
    setAllowedAreas(Qt::AllDockWidgetAreas);
    createCentralWidget();
    setTargetSceneRenderer(targetSceneRenderer);
}

void TargetSceneWrapperWidget::setTargetSceneRenderer(std::shared_ptr<ITargetSceneRenderer> targetSceneRenderer)
{
    _targetSceneRenderer = targetSceneRenderer;

    auto layout = centralWidget->layout();
    if ( layout->count() > 0 ) {
        layout->removeItem(layout->itemAt(0));
    }
    layout->addWidget(_targetSceneRenderer->widget());

    //this->setWidget(_targetSceneRenderer->widget());
}

std::shared_ptr<ITargetSceneRenderer> TargetSceneWrapperWidget::targetSceneRenderer()
{
    return _targetSceneRenderer;
}

void TargetSceneWrapperWidget::setTargetObject(const QString& pathToObject)
{
    if ( !QFile::exists(pathToObject) ) {
        throw std::runtime_error("File " + pathToObject.toStdString() + " not exists!");
    }

    auto targetObject = std::make_shared<TargetObject>();
    targetObject->loadMesh(pathToObject);

    if ( !*targetObject ) {
        throw std::runtime_error("Error on load mesh from file: " + pathToObject.toStdString() + "!");
    }

    _targetSceneRenderer->setTargetObject(targetObject);
}

void TargetSceneWrapperWidget::setTargetObject()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open model");
    dialog.setNameFilter("Model (*.obj *.x *.3ds *.b3d *.blend *.dae *.stl)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    if ( dialog.exec() ) {
        try {
            setTargetObject(dialog.selectedFiles()[0]);
        }
        catch( ... ) {
            QMessageBox::critical(this, "Error!", "Error on load model!");
        }
    }
}

void TargetSceneWrapperWidget::createCentralWidget()
{
    if ( centralWidget ) return;

    centralWidget = new QWidget(this);

    auto layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    auto menuBar = new QMenuBar(centralWidget);
    auto loadAction = menuBar->addAction("Load model");

    layout->setMenuBar(menuBar);
    connect( loadAction
           , &QAction::triggered
           , this
           , [this]() { this->setTargetObject(); } );

    this->setWidget(centralWidget);
}

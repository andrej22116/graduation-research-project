#include "WelcomeWindowDialog.hpp"
#include "ui_WelcomeWindowDialog.h"

#include <QJsonObject>
#include <QFileDialog>

#include <QDebug>
#include <QGraphicsDropShadowEffect>


WelcomeWindowDialog::
WelcomeWindowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeWindowDialog)
{
    ui->setupUi(this);

    ui->centralStackedWidget->setCurrentWidget(ui->welcomPage);
    ui->labelWidget->hide();

    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setWindowTitle("SD: Welcome page");

    connect( ui->exitButton
           , &QPushButton::clicked
           , this
           , [this](){ emit this->exit(); });

    connect( ui->createProjectButton
           , &QPushButton::clicked
           , this
           , &WelcomeWindowDialog::onOpenSolutionCreatorPage );

    connect( ui->openProjectButton
           , &QPushButton::clicked
           , this
           , &WelcomeWindowDialog::onSelectSolutionPath );

    connect( ui->aboutProgrammButton
           , &QPushButton::clicked
           , this
           , &WelcomeWindowDialog::onOpenAboutProgrammPage );

    connect( ui->backToMainButton
           , &QPushButton::clicked
           , this
           , &WelcomeWindowDialog::onComebackToMainPage );

    ui->comboBoxCompiller->addItem("Pisos");
}

WelcomeWindowDialog::
~WelcomeWindowDialog()
{
    delete ui;
}


void
WelcomeWindowDialog::
onSelectSolutionPath()
{
    auto fileName = QFileDialog::getOpenFileName( this
                                                , "Open solution"
                                                , ""
                                                , "Sahder solution (*.sdsln)");
    if ( fileName.size() > 0 ) {
        emit openSolution(fileName);
    }
}


void
WelcomeWindowDialog::
onOpenSolutionCreatorPage()
{
    ui->labelWidget->show();
    ui->pageNameLabel->setText("Create solution");
    ui->centralStackedWidget->setCurrentWidget(ui->projectSettingsPage);
}


void
WelcomeWindowDialog::
onComebackToMainPage()
{
    ui->labelWidget->hide();
    ui->centralStackedWidget->setCurrentWidget(ui->welcomPage);
}


void
WelcomeWindowDialog::
onCreateNewSolution()
{
    QJsonObject solutionProperties;

    emit createSolution("", "", true, solutionProperties);
}


void
WelcomeWindowDialog::
onOpenAboutProgrammPage()
{
    ui->labelWidget->show();
    ui->pageNameLabel->setText("About programm");
    ui->centralStackedWidget->setCurrentWidget(ui->aboutProgrammPage);
}

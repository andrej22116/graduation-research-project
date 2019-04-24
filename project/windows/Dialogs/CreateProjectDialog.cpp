#include "CreateProjectDialog.hpp"
#include "ui_CreateProjectDialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

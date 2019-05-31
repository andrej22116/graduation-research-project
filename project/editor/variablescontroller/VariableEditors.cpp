#include "VariableEditors.hpp"
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "VariableDataModels.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

VariableEditor::
VariableEditor(QWidget* parent)
    : QWidget(parent)
    , isBuilded(false)
{
    auto baseLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    auto variableNameLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    setLayout(baseLayout);
    baseLayout->addItem(variableNameLayout);

    _variableNameLineEdit = new QLineEdit(this);
    _variableNameLineEdit->setPlaceholderText("Variable name...");
    _variableNameLineEdit->setClearButtonEnabled(true);
    _variableNameLineEdit->setReadOnly(true);
    variableNameLayout->addWidget(_variableNameLineEdit);

    _variableNameEditButton = new QPushButton("edit", this);
}


void
VariableEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    _variableDataModel = variableDataModel;
    _variableNameLineEdit->setText(_variableDataModel->name);
}


VariableEditor::VariableDataModelPtr
VariableEditor::
variableDataModel()
{
    return _variableDataModel;
}


void
VariableEditor::
build()
{
    if ( isBuilded ) { return; }

    isBuilded = true;
}


void
VariableEditor::
onBeginEditVariableName()
{
    _variableNameEditButton->setText("save");
    _variableNameLineEdit->setReadOnly(false);
}


void
VariableEditor::
onEndEditVariableName()
{
    _variableNameEditButton->setText("edit");
    _variableNameLineEdit->setReadOnly(true);
}


void
VariableEditor::
setEditWidget(QWidget* widget)
{
    layout()->addWidget(widget);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BooleanVariableEditor::BooleanVariableEditor(QWidget* parent)
{

}

void
BooleanVariableEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

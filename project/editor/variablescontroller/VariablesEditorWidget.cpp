#include "VariablesEditorWidget.hpp"
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>

#include "VariableDataModels.hpp"
#include "VariableValueEditorsFactory.hpp"
#include "VariableValueEditors.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

VariablesEditorWidget::
VariablesEditorWidget(QWidget* parent)
    : QWidget(parent)
    , _editName(false)
{
    auto baseLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    auto variableNameLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    _variableEditorContainer = new QScrollArea(this);
    _variableEditorContainer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _variableEditorContainer->setWidgetResizable(true);

    _variableNameLineEdit = new QLineEdit(this);
    _variableNameLineEdit->setPlaceholderText("Variable name...");
    _variableNameLineEdit->setClearButtonEnabled(true);
    _variableNameLineEdit->setReadOnly(true);
    variableNameLayout->addWidget(_variableNameLineEdit);

    _variableNameEditButton = new QPushButton("edit", this);
    variableNameLayout->addWidget(_variableNameEditButton);
    connect( _variableNameEditButton
           , &QPushButton::clicked
           , this
           , [this]() {
        if ( _editName ) {
            onEndEditVariableName();
            _editName = false;
        }
        else {
            onBeginEditVariableName();
            _editName = true;
        }
    });

    _supportedVariablesTypes = new QComboBox(this);
    _errorMessage = new QLabel(this);
    _errorMessage->hide();
    _errorMessage->setWordWrap(true);

    connect( _supportedVariablesTypes
           , static_cast<void(QComboBox::*)(const QString&)>
                (&QComboBox::currentIndexChanged)
           , this
           , &VariablesEditorWidget::onChacngeVariableType );

    setLayout(baseLayout);
    baseLayout->addWidget(new QLabel("Variable name"));
    baseLayout->addWidget(_errorMessage);
    baseLayout->addItem(variableNameLayout);
    baseLayout->addWidget(new QLabel("Variable type"));
    baseLayout->addWidget(_supportedVariablesTypes);
    baseLayout->addWidget(new QLabel("Variable value"));
    baseLayout->addWidget(_variableEditorContainer);
}


void
VariablesEditorWidget::
setSupportedTypes(const QStringList& supportedTypesList)
{
    if ( _supportedVariablesTypes->count() > 0 ) {
        _supportedVariablesTypes->clear();
    }

    _supportedVariablesTypes->addItems(supportedTypesList);

    int index = 0;
    for ( auto& name : supportedTypesList ) {
        _typeNamesIndexes[name] = index;
        ++index;
    }
}


void
VariablesEditorWidget::
setVariableDataModel( VariableDataModelPtr variableDataModel
                    , const QString& variableTypeName )
{
    _variableDataModel = nullptr;
    _variableNameLineEdit->setText(variableDataModel->name);

    auto index = _typeNamesIndexes[variableTypeName];
    _supportedVariablesTypes->setCurrentIndex(index);

    _variableDataModel = variableDataModel;

    setNewEditor(variableTypeName, false);
}


void
VariablesEditorWidget::
setNewEditor( const QString& typeName
            , bool setDefaultValue )
{
    auto editor = VariableValueEditorsFactory::build(typeName);
    _variableEditorContainer->setWidget(editor);
    editor->setVariableDataModel(_variableDataModel);

    if ( setDefaultValue ) {
        editor->setDefaultValue();
    }
}


VariablesEditorWidget::VariableDataModelPtr
VariablesEditorWidget::
variableDataModel()
{
    return _variableDataModel;
}


void
VariablesEditorWidget::
onBeginEditVariableName()
{
    if ( !_variableDataModel ) {
        return;
    }

    _variableNameEditButton->setText("save");
    _variableNameLineEdit->setReadOnly(false);
}


void
VariablesEditorWidget::
onEndEditVariableName()
{
    _variableNameEditButton->setText("edit");
    _variableNameLineEdit->setReadOnly(true);

    _hasError = false;

    if ( !_variableDataModel ) {
        return;
    }

    emit variableNameChanged( _variableDataModel->name
                            , _variableNameLineEdit->text() );

    if ( _hasError ) {
        _variableNameLineEdit->setText(_variableDataModel->name);
    }
    else {
        _errorMessage->hide();
        _variableDataModel->name = _variableNameLineEdit->text();
    }
}


void
VariablesEditorWidget::
onChangeVariableNameError(const QString& what)
{
    _errorMessage->setText(what);
    _errorMessage->show();
    _hasError = true;
}


void
VariablesEditorWidget::
onChacngeVariableType(const QString& newTypeName)
{
    if ( !_variableDataModel ) {
        return;
    }

    setNewEditor(newTypeName, true);

    emit variableTypeChanged(_variableDataModel->name, newTypeName);
}

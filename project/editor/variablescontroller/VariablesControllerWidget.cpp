#include "VariablesControllerWidget.hpp"
#include "VariablesListWidget.hpp"
#include "VariablesEditorWidget.hpp"
#include "VariablesController.hpp"

#include <QBoxLayout>
#include <QDebug>

#include "VariableDataModelsFactory.hpp"
#include "VariableValueEditorsFactory.hpp"

VariablesControllerWidget::
VariablesControllerWidget( VariablesControllerPtr variablesController
                         , QWidget* parent)
    : QWidget(parent)
    , _variablesEditorWidget(new VariablesEditorWidget(this))
    , _variablesController(variablesController)
{
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    _defaultVariablesWidget = new VariablesListWidget( "Default variables"
                                                     , false
                                                     , this );

    _userVariablesWidget = new VariablesListWidget( "User variables"
                                                  , true
                                                  , this );

    layout->addWidget(_defaultVariablesWidget);
    layout->addWidget(_userVariablesWidget);
    layout->addWidget(_variablesEditorWidget);

    bindDefaultVariablesConnectionsWithController();
    bindUserVariablesConnectionsWithController();
    bindVariablesEditConnectionsWithController();

    _variablesEditorWidget->setSupportedTypes(
                variablesController->supportedVariablesTypes() );
}


void
VariablesControllerWidget::
bindDefaultVariablesConnectionsWithController()
{
    auto& vc = _variablesController;
    vc->connect( _defaultVariablesWidget
               , &VariablesListWidget::variableDoubleClicked
               , vc.get()
               , &VariablesController::onAddVariableToScene );
}


void
VariablesControllerWidget::
bindUserVariablesConnectionsWithController()
{
    auto& vc = _variablesController;
    vc->connect( _userVariablesWidget
               , &VariablesListWidget::variableCreated
               , vc.get()
               , &VariablesController::onCreateVariable );

    vc->connect( vc.get()
               , &VariablesController::variableChangeName
               , _userVariablesWidget
               , &VariablesListWidget::renameVariable );

    vc->connect( _userVariablesWidget
               , &VariablesListWidget::variableRemoved
               , vc.get()
               , &VariablesController::onRemoveVariable );

    vc->connect( _userVariablesWidget
               , &VariablesListWidget::variableDoubleClicked
               , vc.get()
               , &VariablesController::onAddVariableToScene );

    vc->connect( _userVariablesWidget
               , &VariablesListWidget::variableSelected
               , vc.get()
               , &VariablesController::onSelectVariable );
}


void
VariablesControllerWidget::
bindVariablesEditConnectionsWithController()
{
    auto& vc = _variablesController;
    vc->connect( vc.get()
               , &VariablesController::variableSelected
               , _variablesEditorWidget
               , &VariablesEditorWidget::setVariableDataModel );

    vc->connect( _variablesEditorWidget
               , &VariablesEditorWidget::variableNameChanged
               , vc.get()
               , &VariablesController::onRenameVariable );

    vc->connect( _variablesEditorWidget
               , &VariablesEditorWidget::variableTypeChanged
               , vc.get()
               , &VariablesController::onChangeVariableDataModel );
}

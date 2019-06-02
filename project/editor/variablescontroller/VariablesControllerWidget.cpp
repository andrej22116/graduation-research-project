#include "VariablesControllerWidget.hpp"
#include "VariablesListWidget.hpp"
//#include "VariablesEditorWidget.hpp"

#include <QBoxLayout>

VariablesControllerWidget::
VariablesControllerWidget( VariablesControllerPtr variablesController
                         , QWidget* parent)
    : QWidget(parent)
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

    bindDefaultVariablesConnectionsWithController();
    bindUserVariablesConnectionsWithController();
    bindVariablesEditConnectionsWithController();
}


void
VariablesControllerWidget::
bindDefaultVariablesConnectionsWithController()
{

}


void
VariablesControllerWidget::
bindUserVariablesConnectionsWithController()
{

}


void
VariablesControllerWidget::
bindVariablesEditConnectionsWithController()
{

}

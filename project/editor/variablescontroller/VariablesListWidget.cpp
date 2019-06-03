#include "VariablesListWidget.hpp"

#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

#include <stdexcept>

VariablesListWidget::
VariablesListWidget( const QString& name
                   , bool needControls
                   , QWidget* parent )
    : QWidget(parent)
    , _listWidget(new QListWidget(this))
{
    auto layout = new QGridLayout(this);
    setLayout(layout);

    auto label = new QLabel(name, this);
    layout->addWidget(label, 0, 0, 1, 2);

    if ( needControls ) {
        auto buttonAdd = new QPushButton("Add variable", this);
        auto buttonRemove = new QPushButton("Remove variable", this);

        layout->addWidget(buttonAdd, 1, 0);
        layout->addWidget(buttonRemove, 1, 1);

        connect( buttonAdd
               , &QPushButton::clicked
               , this
               , &VariablesListWidget::onCreateVariable );

        connect( buttonRemove
               , &QPushButton::clicked
               , this
               , &VariablesListWidget::onRemoveVariable );
    }

    layout->addWidget(_listWidget, 2, 0, 1, 2);

    _listWidget->setSortingEnabled(true);

    connect( _listWidget
           , &QListWidget::itemClicked
           , this
           , &VariablesListWidget::onSelectVariable );

    connect( _listWidget
           , &QListWidget::itemDoubleClicked
           , this
           , &VariablesListWidget::onDoubleClicked );
}


void
VariablesListWidget::
insertVariable(const QString& name)
{
    if ( _variables.find(name) != _variables.end() ) {
        throw std::runtime_error("Variable already exists!");
    }

    auto item = new QListWidgetItem(name, _listWidget);
    _listWidget->insertItem(0, item);

    _variables[name] = item;

    //item->setFlags(item->flags() | Qt::ItemIsEditable);
}


void
VariablesListWidget::
removeVariable(const QString& name)
{
    auto item = _variables[name];
    _variables.remove(name);

    auto itemIndex = _listWidget->row(item);
    delete _listWidget->takeItem(itemIndex);
}


void
VariablesListWidget::
renameVariable(const QString& oldName, const QString& newName)
{
    if ( _variables.find(oldName) == _variables.end() ) {
        throw std::runtime_error("[VariablesListWidget::renameVariable]:"
                                 " Variable not exists!");
    }

    auto item = _variables[oldName];
    _variables.remove(oldName);

    _variables[newName] = item;
    item->setText(newName);
}


void
VariablesListWidget::
onRemoveVariable()
{
    auto items = _listWidget->selectedItems();
    auto variableName = items[0]->text();
    removeVariable(variableName);

    emit variableRemoved(variableName);
}


void
VariablesListWidget::
onCreateVariable()
{
    QString variableName = "New Variable";
    int index = 1;
    while ( _variables.find(variableName) != _variables.end() ) {
        variableName = QString("New Variable %1").arg(index);
        ++index;
    }

    insertVariable(variableName);
    emit variableCreated(variableName);
}


void
VariablesListWidget::
onSelectVariable(QListWidgetItem* item)
{
    emit variableSelected(item->text());
}


void
VariablesListWidget::
onDoubleClicked(QListWidgetItem* item)
{
    emit variableDoubleClicked(item->text());
}

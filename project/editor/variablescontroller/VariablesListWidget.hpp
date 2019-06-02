#ifndef VARIABLESLISTWIDGET_HPP
#define VARIABLESLISTWIDGET_HPP

#include <QWidget>

class QListWidget;
class QListWidgetItem;

class VariablesListWidget : public QWidget
{
    Q_OBJECT

public:
    VariablesListWidget( const QString& name
                       , bool needControls
                       , QWidget* parent = nullptr );

    void
    insertVariable(const QString& name);

    void
    removeVariable(const QString& name);

    void
    renameVariable( const QString& oldName
                  , const QString& newName );

signals:
    void
    variableRemoved(const QString& name);

    void
    variableCreated(const QString& name);

    void
    variableDoubleClicked(const QString& name);

private slots:
    void
    onRemoveVariable();

    void
    onCreateVariable();

    void
    onDoubleClicked(QListWidgetItem* item);

private:
    QListWidget* _listWidget;
    QHash<QString, QListWidgetItem*> _variables;
};

#endif // VARIABLESLISTWIDGET_HPP

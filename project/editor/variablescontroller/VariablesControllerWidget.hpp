#ifndef VARIABLESCONTROLLERWIDGET_HPP
#define VARIABLESCONTROLLERWIDGET_HPP

#include <QWidget>
#include <memory>

class VariablesListWidget;
class VariablesEditorWidget;
class VariablesController;

class VariablesControllerWidget : public QWidget
{
    Q_OBJECT
public:
    using VariablesControllerPtr = std::shared_ptr<VariablesController>;

    explicit
    VariablesControllerWidget( VariablesControllerPtr variablesController
                             , QWidget *parent = nullptr );

private:
    void
    bindDefaultVariablesConnectionsWithController();

    void
    bindUserVariablesConnectionsWithController();

    void
    bindVariablesEditConnectionsWithController();

private:
    VariablesListWidget* _defaultVariablesWidget;
    VariablesListWidget* _userVariablesWidget;
    VariablesEditorWidget* _variablesEditorWidget;

    VariablesControllerPtr _variablesController;
};

#endif // VARIABLESCONTROLLERWIDGET_HPP

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
    VariablesControllerWidget( VariablesControllerPtr variableController
                             , QWidget *parent = nullptr );

private:
    VariablesListWidget* _variablesWidget;
    VariablesEditorWidget* _variablesEditorWidget;

    VariablesControllerPtr _controller;
};

#endif // VARIABLESCONTROLLERWIDGET_HPP

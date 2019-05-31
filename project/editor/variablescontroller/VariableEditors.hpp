#ifndef VARIABLEEDITORS_HPP
#define VARIABLEEDITORS_HPP

#include <QWidget>
#include <memory>

class VariableDataModel;
class QPushButton;
class QLineEdit;

class VariableEditor : public QWidget
{
    Q_OBJECT

public:
    explicit VariableEditor(QWidget* parent = nullptr);

    using VariableDataModelPtr = std::shared_ptr<VariableDataModel>;

    virtual void
    setVariableDataModel(VariableDataModelPtr variableDataModel);

    void
    setVariablesControllers(VariableDataModelPtr variableDataModel);

    VariableDataModelPtr
    variableDataModel();

    void
    build();

signals:
    void
    changedVariableName(const QString& newVariableName);

public slots:
    void
    onBeginEditVariableName();

    void
    onEndEditVariableName();

protected:
    void setEditWidget(QWidget* widget);

private:
    bool isBuilded;
    VariableDataModelPtr _variableDataModel;
    QPushButton* _variableNameEditButton;
    QLineEdit* _variableNameLineEdit;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BooleanVariableEditor : public VariableEditor {
    Q_OBJECT

public:
    BooleanVariableEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;
};

#endif // VARIABLEEDITORS_HPP

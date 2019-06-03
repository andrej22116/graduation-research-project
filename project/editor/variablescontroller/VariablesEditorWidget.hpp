#ifndef VARIABLEEDITORS_HPP
#define VARIABLEEDITORS_HPP

#include <QWidget>
#include <memory>

class VariableDataModel;
class QPushButton;
class QLineEdit;
class QScrollArea;
class QComboBox;
class QLabel;

class VariablesEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VariablesEditorWidget(QWidget* parent = nullptr);

    using VariableDataModelPtr = std::shared_ptr<VariableDataModel>;

    void
    setSupportedTypes(const QStringList& supportedTypesList);

    VariableDataModelPtr
    variableDataModel();

signals:
    void
    variableNameChanged( const QString& oldName
                       , const QString& newName );

    void
    variableTypeChanged( const QString& variableName
                       , const QString& newTypeName );

public slots:
    void
    onBeginEditVariableName();

    void
    onEndEditVariableName();

    void
    onChangeVariableNameError(const QString& what);

    void
    onChacngeVariableType(const QString& newTypeName);

    void
    setVariableDataModel( VariableDataModelPtr variableDataModel
                        , const QString& dataTypeName );

private:
    void
    setNewEditor( const QString& typeName
                , bool setDefaultValue );

private:
    VariableDataModelPtr _variableDataModel;
    QPushButton* _variableNameEditButton;
    QLineEdit* _variableNameLineEdit;
    QScrollArea* _variableEditorContainer;
    QComboBox* _supportedVariablesTypes;
    QLabel* _errorMessage;

    QHash<QString, int> _typeNamesIndexes;

    bool _hasError;
    bool _editName;
};

#endif // VARIABLEEDITORS_HPP

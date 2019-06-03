#ifndef VARIABLEVALUEEDITORS_HPP
#define VARIABLEVALUEEDITORS_HPP

#include <QWidget>
#include <memory>
#include <array>

class VariableDataModel;
class QCheckBox;
class QLineEdit;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class VariableValueEditor : public QWidget
{
public:
    VariableValueEditor(QWidget* parent = nullptr);

    using VariableDataModelPtr = std::shared_ptr<VariableDataModel>;

    virtual void
    setVariableDataModel(VariableDataModelPtr variableDataModel);

    VariableDataModelPtr
    variableDataModel();

    virtual void
    setDefaultValue() = 0;

private:
    VariableDataModelPtr _variableDataModel;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class IntegerValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    IntegerValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    QLineEdit* _valueEdit;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class UnsignedIntegerValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    UnsignedIntegerValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    QLineEdit* _valueEdit;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class FloatValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    FloatValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    QLineEdit* _valueEdit;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DoubleValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    DoubleValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    QLineEdit* _valueEdit;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BooleanValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    BooleanValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    QCheckBox* _valueCheckBox;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vector2ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Vector2ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<QLineEdit*, 2> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vector3ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Vector3ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<QLineEdit*, 3> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vector4ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Vector4ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<QLineEdit*, 4> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Matrix2x2ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Matrix2x2ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<std::array<QLineEdit*, 2>, 2> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Matrix3x3ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Matrix3x3ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<std::array<QLineEdit*, 3>, 3> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Matrix4x4ValueEditor : public VariableValueEditor {
    Q_OBJECT

public:
    Matrix4x4ValueEditor(QWidget* parent = nullptr);

    void
    setVariableDataModel(VariableDataModelPtr variableDataModel) override;

    void
    setDefaultValue() override;

private:
    std::array<std::array<QLineEdit*, 4>, 4> _valuesEditors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif // VARIABLEVALUEEDITORS_HPP

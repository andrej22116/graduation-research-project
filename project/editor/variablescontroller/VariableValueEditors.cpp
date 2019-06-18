#include "VariableValueEditors.hpp"

#include <QGridLayout>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <cinttypes>
#include <cfloat>
#include <QLocale>

#include "VariableDataModels.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template<typename T>
std::shared_ptr<T>
modelFromEditor(VariableValueEditor* editor) {
    return std::static_pointer_cast<T>(editor->variableDataModel());
}

template<typename T>
std::shared_ptr<T>
modelToModel(std::shared_ptr<VariableDataModel> model) {
    return std::static_pointer_cast<T>(model);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

VariableValueEditor::
VariableValueEditor(QWidget* parent)
    : QWidget(parent)
{
}


void
VariableValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    _variableDataModel = variableDataModel;
}


VariableValueEditor::VariableDataModelPtr
VariableValueEditor::
variableDataModel()
{
    return _variableDataModel;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

IntegerValueEditor::
IntegerValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    _valueEdit = new QLineEdit("0", this);

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto validator = new QIntValidator(INT32_MIN, INT32_MAX, _valueEdit);

    _valueEdit->setValidator(validator);

    layout->addWidget(_valueEdit);
    setLayout(layout);

    connect( _valueEdit
           , &QLineEdit::textChanged
           , this
           , [this](const QString& valueStr) {
        if ( valueStr.size() == 0 ) {
            _valueEdit->setText("0");
            return;
        }

        auto value = valueStr.toInt();
        auto variable = modelFromEditor<IntegerDataModel>(this);

        if ( !variable ) {
            return;
        }

        variable->value = value;
    });
}


void
IntegerValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<IntegerDataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    _valueEdit->setText(QString::number(variable->value));
}


void
IntegerValueEditor::
setDefaultValue()
{
    _valueEdit->setText("0");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

UnsignedIntegerValueEditor::
UnsignedIntegerValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    _valueEdit = new QLineEdit("0", this);

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto validator = new QIntValidator(0, UINT32_MAX, _valueEdit);

    _valueEdit->setValidator(validator);

    layout->addWidget(_valueEdit);
    setLayout(layout);

    connect( _valueEdit
           , &QLineEdit::textChanged
           , this
           , [this](const QString& valueStr) {
        if ( valueStr.size() == 0 ) {
            _valueEdit->setText("0");
            return;
        }

        auto value = valueStr.toUInt();
        auto variable = modelFromEditor<UnsignedIntegerDataModel>(this);

        if ( !variable ) {
            return;
        }

        variable->value = value;
    });
}


void
UnsignedIntegerValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<UnsignedIntegerDataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    _valueEdit->setText(QString::number(variable->value));
}


void
UnsignedIntegerValueEditor::
setDefaultValue()
{
    _valueEdit->setText("0");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

FloatValueEditor::
FloatValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    _valueEdit = new QLineEdit("0", this);

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto validator = new QDoubleValidator(FLT_MIN, FLT_MAX, 6, _valueEdit);
    validator->setLocale(QLocale{QLocale::C});

    _valueEdit->setValidator(validator);

    layout->addWidget(_valueEdit);
    setLayout(layout);

    connect( _valueEdit
           , &QLineEdit::textChanged
           , this
           , [this](const QString& valueStr) {
        if ( valueStr.size() == 0 ) {
            _valueEdit->setText("0");
            return;
        }

        auto value = valueStr.toFloat();
        auto variable = modelFromEditor<FloatDataModel>(this);

        if ( !variable ) {
            return;
        }

        variable->value = value;
    });
}


void
FloatValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<FloatDataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    _valueEdit->setText(QString::number(variable->value));
}


void
FloatValueEditor::
setDefaultValue()
{
    _valueEdit->setText("0");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DoubleValueEditor::
DoubleValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    _valueEdit = new QLineEdit("0", this);

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto validator = new QDoubleValidator(DBL_MIN, DBL_MAX, 15, _valueEdit);
    validator->setLocale(QLocale{QLocale::C});

    _valueEdit->setValidator(validator);

    layout->addWidget(_valueEdit);
    setLayout(layout);

    connect( _valueEdit
           , &QLineEdit::textChanged
           , this
           , [this](const QString& valueStr) {
        if ( valueStr.size() == 0 ) {
            _valueEdit->setText("0");
            return;
        }

        auto value = valueStr.toDouble();
        auto variable = modelFromEditor<DoubleDataModel>(this);

        if ( !variable ) {
            return;
        }

        variable->value = value;
    });
}


void
DoubleValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<DoubleDataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    _valueEdit->setText(QString::number(variable->value));
}


void
DoubleValueEditor::
setDefaultValue()
{
    _valueEdit->setText("0");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BooleanValueEditor::
BooleanValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    _valueCheckBox = new QCheckBox("Is TRUE", this);

    layout->addWidget(_valueCheckBox);
    setLayout(layout);

    connect( _valueCheckBox
           , &QCheckBox::clicked
           , this
           , [this](bool state) {
        auto variable = modelFromEditor<BooleanDataModel>(this);
        if ( !variable ) {
            return;
        }

        variable->value = state;
    });
}


void
BooleanValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<BooleanDataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    _valueCheckBox->setChecked(variable->value);
}


void
BooleanValueEditor::
setDefaultValue()
{
    _valueCheckBox->setChecked(false);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vector2ValueEditor::
Vector2ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    auto validator = new QDoubleValidator( static_cast<double>(FLT_MIN)
                                         , static_cast<double>(FLT_MAX)
                                         , 6, this);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        editor = new QLineEdit("0", this);
        editor->setValidator(validator);
        layout->addWidget(editor);

        connect( editor
               , &QLineEdit::textChanged
               , this
               , [this, index](const QString& text) {
            auto variable = modelFromEditor<Vec2DataModel>(this);
            if ( !variable ) {
                return;
            }

            variable->value[index] = text.toFloat();
        });

        ++index;
    }
}


void
Vector2ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<Vec2DataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        auto number = static_cast<double>(variable->value[index]);
        editor->setText(QString::number(number));
        ++index;
    }
}


void
Vector2ValueEditor::
setDefaultValue()
{
    for ( auto& editor : _valuesEditors ) {
        editor->setText("0");
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vector3ValueEditor::
Vector3ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    auto validator = new QDoubleValidator( static_cast<double>(FLT_MIN)
                                         , static_cast<double>(FLT_MAX)
                                         , 6, this);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        editor = new QLineEdit("0", this);
        editor->setValidator(validator);
        layout->addWidget(editor);

        connect( editor
               , &QLineEdit::textEdited
               , this
               , [this, index](const QString& text) {
            auto variable = modelFromEditor<Vec2DataModel>(this);
            if ( !variable ) {
                return;
            }

            variable->value[index] = text.toFloat();
        });

        ++index;
    }
}


void
Vector3ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<Vec2DataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        auto number = static_cast<double>(variable->value[index]);
        editor->setText(QString::number(number));
        ++index;
    }
}


void
Vector3ValueEditor::
setDefaultValue()
{
    for ( auto& editor : _valuesEditors ) {
        editor->setText("0");
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vector4ValueEditor::
Vector4ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{
    auto validator = new QDoubleValidator( static_cast<double>(FLT_MIN)
                                         , static_cast<double>(FLT_MAX)
                                         , 6, this);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        editor = new QLineEdit("0", this);
        editor->setValidator(validator);
        layout->addWidget(editor);

        connect( editor
               , &QLineEdit::textEdited
               , this
               , [this, index](const QString& text) {
            auto variable = modelFromEditor<Vec2DataModel>(this);
            if ( !variable ) {
                return;
            }

            variable->value[index] = text.toFloat();
        });

        ++index;
    }
}


void
Vector4ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{
    VariableValueEditor::setVariableDataModel(variableDataModel);

    auto variable = modelToModel<Vec2DataModel>(variableDataModel);
    if ( !variable ) {
        return;
    }

    size_t index = 0;
    for ( auto& editor : _valuesEditors ) {
        auto number = static_cast<double>(variable->value[index]);
        editor->setText(QString::number(number));
        ++index;
    }
}


void
Vector4ValueEditor::
setDefaultValue()
{
    for ( auto& editor : _valuesEditors ) {
        editor->setText("0");
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Matrix2x2ValueEditor::
Matrix2x2ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{

}


void
Matrix2x2ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{

}


void
Matrix2x2ValueEditor::
setDefaultValue()
{

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Matrix3x3ValueEditor::
Matrix3x3ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{

}


void
Matrix3x3ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{

}


void
Matrix3x3ValueEditor::
setDefaultValue()
{

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Matrix4x4ValueEditor::
Matrix4x4ValueEditor(QWidget* parent)
    : VariableValueEditor(parent)
{

}


void
Matrix4x4ValueEditor::
setVariableDataModel(VariableDataModelPtr variableDataModel)
{

}


void
Matrix4x4ValueEditor::
setDefaultValue()
{

}

#include "VariableWidgets.hpp"
#include <QJsonValue>
#include <QLineEdit>
#include <QCheckBox>
#include <QPixmap>
#include <QGridLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonArray>


VariableWidget::VariableWidget(QWidget* parent) :
    QWidget(parent)
{
    auto layout = new QGridLayout;
    setLayout(layout);
    setWindowTitle("PIZDA");

    layout->addWidget(new QLabel("Value "), 0, 0);
}

QString VariableWidget::errorMessage()
{
    return "";
}

SingleValueVariableWidget::SingleValueVariableWidget( QValidator* validator
                                                    , QWidget* parent )
    : VariableWidget(parent)
{
    _valueEdit = new QLineEdit(this);

    _valueEdit->setValidator(validator);

    dynamic_cast<QGridLayout*>(layout())->addWidget(_valueEdit, 0, 1);

    _valueEdit->setFixedSize(_valueEdit->sizeHint());
}

QJsonValue SingleValueVariableWidget::value()
{
    return { _valueEdit->text() };
}

BooleanVariableWidget::BooleanVariableWidget(QWidget* parent)
    : VariableWidget(parent)
{
    _checkBox = new QCheckBox(this);
    _checkBox->setText("False");
    dynamic_cast<QGridLayout*>(layout())->addWidget(_checkBox, 0, 1);

    connect(_checkBox, &QCheckBox::toggled, _checkBox, [this](bool checked){
        if ( checked ) { _checkBox->setText("True"); }
        else { _checkBox->setText("False"); }

        _checkBox->setFixedSize(_checkBox->sizeHint());
    });

    _checkBox->setFixedSize(_checkBox->sizeHint());
}

QJsonValue BooleanVariableWidget::value()
{
    return { _checkBox->isChecked() };
}

Vec2VariableWidget::Vec2VariableWidget( QValidator* validator
                                      , QWidget* parent )
    : VariableWidget(parent)
{
    _vec[0] = new QLineEdit(this);
    _vec[1] = new QLineEdit(this);

    _vec[0]->setValidator(validator);
    //_vec[1]->setValidator(validator);

    auto layout = dynamic_cast<QGridLayout*>(this->layout());

    layout->addWidget(new QLabel("x "), 1, 0);
    layout->addWidget(_vec[0], 1, 1);

    layout->addWidget(new QLabel("y "), 2, 0);
    layout->addWidget(_vec[1], 2, 1);

    _vec[0]->setFixedSize(_vec[0]->sizeHint());
    _vec[1]->setFixedSize(_vec[1]->sizeHint());
}

QJsonValue Vec2VariableWidget::value()
{
    return { QJsonArray { { _vec[0]->text() }
                        , { _vec[1]->text() } }
           };
}

Vec3VariableWidget::Vec3VariableWidget( QValidator* validator
                                        , QWidget* parent )
      : VariableWidget(parent)
{
    _vec[0] = new QLineEdit(this);
    _vec[1] = new QLineEdit(this);
    _vec[2] = new QLineEdit(this);

    _vec[0]->setValidator(validator);
    //_vec[1]->setValidator(validator);
    //_vec[2]->setValidator(validator);

    auto layout = dynamic_cast<QGridLayout*>(this->layout());

    layout->addWidget(new QLabel("x "), 1, 0);
    layout->addWidget(_vec[0], 1, 1);

    layout->addWidget(new QLabel("y "), 2, 0);
    layout->addWidget(_vec[1], 2, 1);

    layout->addWidget(new QLabel("z "), 3, 0);
    layout->addWidget(_vec[0], 3, 1);

    _vec[0]->setFixedSize(_vec[0]->sizeHint());
    _vec[1]->setFixedSize(_vec[1]->sizeHint());
    _vec[2]->setFixedSize(_vec[2]->sizeHint());
}

QJsonValue Vec3VariableWidget::value()
{
    return { QJsonArray { { _vec[0]->text() }
                        , { _vec[1]->text() }
                        , { _vec[2]->text() } }
           };
}

Vec4VariableWidget::Vec4VariableWidget( QValidator* validator
                                      , QWidget* parent )
      : VariableWidget(parent)
{
    _vec[0] = new QLineEdit(this);
    _vec[1] = new QLineEdit(this);
    _vec[2] = new QLineEdit(this);
    _vec[3] = new QLineEdit(this);

    _vec[0]->setValidator(validator);
    //_vec[1]->setValidator(validator);
    //_vec[2]->setValidator(validator);
    //_vec[3]->setValidator(validator);

    auto layout = dynamic_cast<QGridLayout*>(this->layout());

    layout->addWidget(new QLabel("x/r "), 1, 0);
    layout->addWidget(_vec[0], 1, 1);

    layout->addWidget(new QLabel("y/g "), 2, 0);
    layout->addWidget(_vec[1], 2, 1);

    layout->addWidget(new QLabel("z/b "), 3, 0);
    layout->addWidget(_vec[0], 3, 1);

    layout->addWidget(new QLabel("w/a "), 4, 0);
    layout->addWidget(_vec[0], 4, 1);

    _vec[0]->setFixedSize(_vec[0]->sizeHint());
    _vec[1]->setFixedSize(_vec[1]->sizeHint());
    _vec[2]->setFixedSize(_vec[2]->sizeHint());
    _vec[3]->setFixedSize(_vec[3]->sizeHint());
}

QJsonValue Vec4VariableWidget::value()
{
    return { QJsonArray { { _vec[0]->text() }
                        , { _vec[1]->text() }
                        , { _vec[2]->text() }
                        , { _vec[3]->text() } }
           };
}

Matrix2VariableWidget::Matrix2VariableWidget(QValidator* validator, QWidget* parent)
{
    auto layout = dynamic_cast<QGridLayout*>(this->layout());
    const size_t MATRIX_SIZE = 2;

    for (size_t y = 0; y < MATRIX_SIZE; ++y) {
        for (size_t x = 0; x < MATRIX_SIZE; ++x) {
            size_t index = y * MATRIX_SIZE + x;

            _mat[index] = new QLineEdit;
            layout->addWidget(_mat[index], y + 1, x);

            connect( _mat[index], &QLineEdit::textChanged
                   , this, [this](const QString&){
                emit valueChanged();
            });

            _mat[index]->setFixedSize(_mat[index]->sizeHint());
        }
    }
}

QJsonValue Matrix2VariableWidget::value()
{
    QJsonArray array;

    for (size_t i = 0; i < 4; ++i) {
        array.push_back({ _mat[i]->text() });
    }

    return array;
}

Matrix3VariableWidget::Matrix3VariableWidget(QValidator* validator, QWidget* parent)
{
    auto layout = dynamic_cast<QGridLayout*>(this->layout());
    const size_t MATRIX_SIZE = 3;

    for (size_t y = 0; y < MATRIX_SIZE; ++y) {
        for (size_t x = 0; x < MATRIX_SIZE; ++x) {
            size_t index = y * MATRIX_SIZE + x;

            _mat[index] = new QLineEdit;
            layout->addWidget(_mat[index], y + 1, x);

            connect( _mat[index], &QLineEdit::textChanged
                   , this, [this](const QString&){
                emit valueChanged();
            });

            _mat[index]->setFixedSize(_mat[index]->sizeHint());
        }
    }
}

QJsonValue Matrix3VariableWidget::value()
{
    QJsonArray array;

    for (size_t i = 0; i < 9; ++i) {
        array.push_back({ _mat[i]->text() });
    }

    return array;
}

Matrix4VariableWidget::Matrix4VariableWidget(QValidator* validator, QWidget* parent)
{
    auto layout = dynamic_cast<QGridLayout*>(this->layout());
    const size_t MATRIX_SIZE = 4;

    for (size_t y = 0; y < MATRIX_SIZE; ++y) {
        for (size_t x = 0; x < MATRIX_SIZE; ++x) {
            size_t index = y * MATRIX_SIZE + x;

            _mat[index] = new QLineEdit;
            layout->addWidget(_mat[index], y + 1, x);

            connect( _mat[index], &QLineEdit::textChanged
                   , this, [this](const QString&){
                emit valueChanged();
            });

            _mat[index]->setFixedSize(_mat[index]->sizeHint());
        }
    }
}

QJsonValue Matrix4VariableWidget::value()
{
    QJsonArray array;

    for (size_t i = 0; i < 16; ++i) {
        array.push_back({ _mat[i]->text() });
    }

    return array;
}

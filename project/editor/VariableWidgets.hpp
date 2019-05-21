#ifndef VARIABLEWIDGETS_HPP
#define VARIABLEWIDGETS_HPP

#include <QWidget>
//#include <QLineEdit>
//#include <QJsonValue>

class QJsonValue;
class QLineEdit;
class QValidator;
class QCheckBox;

class VariableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VariableWidget(QWidget* parent = nullptr);

    /// Value on JSON format
    virtual QJsonValue value() = 0;

    /// Validation test
    virtual bool isValid() { return true; }

    /// Error message. Using this, if isValid return false
    virtual QString errorMessage();

signals:
    /// This signal is sent when the variable changes
    /// and its value may contain errors.
    void valueChanged();
};


/// Widget with single field for edit variable / decimal / integer / other /
class SingleValueVariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit SingleValueVariableWidget( QValidator* validator
                                      , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _valueEdit;
};


/// Boolean variable / true / false /
class BooleanVariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit BooleanVariableWidget(QWidget* parent = nullptr);

    QJsonValue value() override;

private:
    QCheckBox* _checkBox;
};


class Vec2VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Vec2VariableWidget( QValidator* validator
                               , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _vec[2];
};


class Vec3VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Vec3VariableWidget( QValidator* validator
                               , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _vec[3];
};


class Vec4VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Vec4VariableWidget( QValidator* validator
                               , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _vec[4];
};


class Matrix2VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Matrix2VariableWidget( QValidator* validator
                                  , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _mat[4];
};


class Matrix3VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Matrix3VariableWidget( QValidator* validator
                                  , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _mat[9];
};


class Matrix4VariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Matrix4VariableWidget( QValidator* validator
                                  , QWidget* parent = nullptr );

    QJsonValue value() override;

private:
    QLineEdit* _mat[16];
};

/*
class Texture2DVariableWidget : public VariableWidget {
    Q_OBJECT

public:
    explicit Texture2DVariableWidget(QWidget* parent = nullptr);

    QJsonValue value() override;

private:
    QPixmap _image;
};
*/

#endif // VARIABLEWIDGETS_HPP

#include "ConstVariablesNodes.hpp"

#include "GlobalConstants.hpp"
#include "ShaderNodeDataTypes.hpp"

#include <QLineEdit>
#include <QCheckBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QLocale>
#include <QBoxLayout>
#include <cinttypes>
#include <cfloat>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

FloatConstVariableNode::
FloatConstVariableNode()
{
    _widget = new QLineEdit("");
    _widget->setMaximumWidth(75);
    auto validator = new QDoubleValidator(-FLT_MAX, FLT_MAX, 6, _widget);
    validator->setLocale(QLocale{QLocale::C});
    _widget->setValidator(validator);
}


QJsonObject
FloatConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = _widget->text();

    return obj;
}


void
FloatConstVariableNode::
restore(const QJsonObject& obj)
{
    _widget->setText(obj[JSON_VALUE].toString());
}


QString
FloatConstVariableNode::
caption() const
{
    return "Const float";
}


QString
FloatConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
FloatConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
FloatConstVariableNode::
name() const
{
    return "const_float";
}


unsigned int
FloatConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
FloatConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return FloatDataType{};
}


QWidget*
FloatConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DoubleConstVariableNode::
DoubleConstVariableNode()
{
    _widget = new QLineEdit("");
    _widget->setMaximumWidth(75);
    auto validator = new QDoubleValidator(-DBL_MAX, DBL_MAX, 12, _widget);
    validator->setLocale(QLocale{QLocale::C});
    _widget->setValidator(validator);
}


QJsonObject
DoubleConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = _widget->text();

    return obj;
}


void
DoubleConstVariableNode::
restore(const QJsonObject& obj)
{
    _widget->setText(obj[JSON_VALUE].toString());
}


QString
DoubleConstVariableNode::
caption() const
{
    return "Const double";
}


QString
DoubleConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
DoubleConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
DoubleConstVariableNode::
name() const
{
    return "const_double";
}


unsigned int
DoubleConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
DoubleConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return DoubleDataType{};
}


QWidget*
DoubleConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BooleanConstVariableNode::
BooleanConstVariableNode()
{
    _widget = new QCheckBox;
    _widget->setText("False");
    connect( _widget
           , &QCheckBox::clicked
           , this
           , [this](bool checked){
        if ( checked ) {
            _widget->setText("True");
        }
        else {
            _widget->setText("False");
        }
    });

    _widget->setStyleSheet(".QCheckBox{background-color:transparent;} "
                           "*{color:white;}");
}


QJsonObject
BooleanConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = _widget->isChecked();

    return obj;
}


void
BooleanConstVariableNode::
restore(const QJsonObject& obj)
{
    _widget->setChecked(obj[JSON_VALUE].toBool());
}


QString
BooleanConstVariableNode::
caption() const
{
    return "Const boolean";
}


QString
BooleanConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
BooleanConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
BooleanConstVariableNode::
name() const
{
    return "const_bool";
}


unsigned int
BooleanConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
BooleanConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return BooleanDataType{};
}


QWidget*
BooleanConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

IntegerConstVariableNode::
IntegerConstVariableNode()
{
    _widget = new QLineEdit("");
    _widget->setMaximumWidth(75);
    auto validator = new QIntValidator(INT_MIN, INT_MAX, _widget);
    validator->setLocale(QLocale{QLocale::C});
    _widget->setValidator(validator);
}


QJsonObject
IntegerConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = _widget->text();

    return obj;
}


void
IntegerConstVariableNode::
restore(const QJsonObject& obj)
{
    _widget->setText(obj[JSON_VALUE].toString());
}


QString
IntegerConstVariableNode::
caption() const
{
    return "Const integer";
}


QString
IntegerConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
IntegerConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
IntegerConstVariableNode::
name() const
{
    return "const_integer";
}


unsigned int
IntegerConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
IntegerConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return IntegerDataType{};
}


QWidget*
IntegerConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

UnsignedIntegerConstVariableNode::
UnsignedIntegerConstVariableNode()
{
    _widget = new QLineEdit("");
    _widget->setMaximumWidth(75);
    auto validator = new QIntValidator(0, UINT_MAX, _widget);
    validator->setLocale(QLocale{QLocale::C});
    _widget->setValidator(validator);
}


QJsonObject
UnsignedIntegerConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = _widget->text();

    return obj;
}


void
UnsignedIntegerConstVariableNode::
restore(const QJsonObject& obj)
{
    _widget->setText(obj[JSON_VALUE].toString());
}


QString
UnsignedIntegerConstVariableNode::
caption() const
{
    return "Const unsigned int";
}


QString
UnsignedIntegerConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
UnsignedIntegerConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
UnsignedIntegerConstVariableNode::
name() const
{
    return "const_uinteger";
}


unsigned int
UnsignedIntegerConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
UnsignedIntegerConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return UnsignedIntegerDataType{};
}


QWidget*
UnsignedIntegerConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vec2ConstVariableNode::
Vec2ConstVariableNode()
{
    _widget = new QWidget();
    auto validator = new QDoubleValidator(-FLT_MAX, FLT_MAX, 6, _widget);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, _widget);

    for ( auto& edit : _editors ) {
        edit = new QLineEdit(_widget);
        edit->setValidator(validator);
        edit->setMaximumWidth(75);

        layout->addWidget(edit);
    }

    _editors[0]->setPlaceholderText("x/r");
    _editors[1]->setPlaceholderText("y/g");

    _widget->setLayout(layout);
    _widget->setFixedSize(_widget->sizeHint());
    _widget->setStyleSheet(".QWidget{background-color:transparent;}");
}


QJsonObject
Vec2ConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = QJsonObject{
        {"r", _editors[0]->text()},
        {"g", _editors[1]->text()}
    };

    return obj;
}


void
Vec2ConstVariableNode::
restore(const QJsonObject& obj)
{
    auto valueObj = obj[JSON_VALUE].toObject();
    _editors[0]->setText(valueObj["r"].toString());
    _editors[1]->setText(valueObj["g"].toString());
}


QString
Vec2ConstVariableNode::
caption() const
{
    return "Const vec2";
}


QString
Vec2ConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
Vec2ConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
Vec2ConstVariableNode::
name() const
{
    return "const_vec2";
}


unsigned int
Vec2ConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
Vec2ConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return Vec2DataType{};
}


QWidget*
Vec2ConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vec3ConstVariableNode::
Vec3ConstVariableNode()
{
    _widget = new QWidget();
    auto validator = new QDoubleValidator(-FLT_MAX, FLT_MAX, 6, _widget);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, _widget);

    for ( auto& edit : _editors ) {
        edit = new QLineEdit(_widget);
        edit->setValidator(validator);
        edit->setMaximumWidth(75);

        layout->addWidget(edit);
    }

    _editors[0]->setPlaceholderText("x/r");
    _editors[1]->setPlaceholderText("y/g");
    _editors[2]->setPlaceholderText("z/b");

    _widget->setLayout(layout);
    _widget->setFixedSize(_widget->sizeHint());
    _widget->setStyleSheet(".QWidget{background-color:transparent;}");
}


QJsonObject
Vec3ConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = QJsonObject{
        {"r", _editors[0]->text()},
        {"g", _editors[1]->text()},
        {"b", _editors[2]->text()}
    };

    return obj;
}


void
Vec3ConstVariableNode::
restore(const QJsonObject& obj)
{
    auto valueObj = obj[JSON_VALUE].toObject();
    _editors[0]->setText(valueObj["r"].toString());
    _editors[1]->setText(valueObj["g"].toString());
    _editors[2]->setText(valueObj["b"].toString());
}


QString
Vec3ConstVariableNode::
caption() const
{
    return "Const vec3";
}


QString
Vec3ConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
Vec3ConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
Vec3ConstVariableNode::
name() const
{
    return "const_vec3";
}


unsigned int
Vec3ConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
Vec3ConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return Vec3DataType{};
}


QWidget*
Vec3ConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Vec4ConstVariableNode::
Vec4ConstVariableNode()
{
    _widget = new QWidget();
    auto validator = new QDoubleValidator(-FLT_MAX, FLT_MAX, 6, _widget);
    validator->setLocale(QLocale{QLocale::C});

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, _widget);

    for ( auto& edit : _editors ) {
        edit = new QLineEdit(_widget);
        edit->setValidator(validator);
        edit->setMaximumWidth(75);

        layout->addWidget(edit);
    }

    _editors[0]->setPlaceholderText("x/r");
    _editors[1]->setPlaceholderText("y/g");
    _editors[2]->setPlaceholderText("z/b");
    _editors[3]->setPlaceholderText("w/a");

    _widget->setLayout(layout);
    _widget->setFixedSize(_widget->sizeHint());
    _widget->setStyleSheet(".QWidget{background-color:transparent;}");
}


QJsonObject
Vec4ConstVariableNode::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();

    obj[JSON_TYPE] = JSON_TYPE_CONST_VARIABLE;
    obj[JSON_VALUE] = QJsonObject{
        {"r", _editors[0]->text()},
        {"g", _editors[1]->text()},
        {"b", _editors[2]->text()},
        {"a", _editors[3]->text()}
    };

    return obj;
}


void
Vec4ConstVariableNode::
restore(const QJsonObject& obj)
{
    auto valueObj = obj[JSON_VALUE].toObject();
    _editors[0]->setText(valueObj["r"].toString());
    _editors[1]->setText(valueObj["g"].toString());
    _editors[2]->setText(valueObj["b"].toString());
    _editors[3]->setText(valueObj["a"].toString());
}


QString
Vec4ConstVariableNode::
caption() const
{
    return "Const vec4";
}


QString
Vec4ConstVariableNode::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex ) const
{
    return "";
}


bool
Vec4ConstVariableNode::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex ) const
{
    return true;
}


QString
Vec4ConstVariableNode::
name() const
{
    return "const_vec4";
}


unsigned int
Vec4ConstVariableNode::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::Out ? 1 : 0;
}


QtNodes::NodeDataType
Vec4ConstVariableNode::
dataType( QtNodes::PortType
        , QtNodes::PortIndex ) const
{
    return Vec4DataType{};
}


QWidget*
Vec4ConstVariableNode::
embeddedWidget()
{
    return _widget;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

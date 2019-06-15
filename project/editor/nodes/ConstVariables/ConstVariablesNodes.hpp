#ifndef CONSTVARIABLESNODES_HPP
#define CONSTVARIABLESNODES_HPP

#include <nodes/NodeDataModel>
#include <array>

class QLineEdit;
class QCheckBox;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class FloatConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    FloatConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QLineEdit* _widget;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DoubleConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    DoubleConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QLineEdit* _widget;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BooleanConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    BooleanConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QCheckBox* _widget;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class IntegerConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    IntegerConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QLineEdit* _widget;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class UnsignedIntegerConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    UnsignedIntegerConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QLineEdit* _widget;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vec2ConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    Vec2ConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QWidget* _widget;
    std::array<QLineEdit*, 2> _editors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vec3ConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    Vec3ConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QWidget* _widget;
    std::array<QLineEdit*, 3> _editors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Vec4ConstVariableNode : public QtNodes::NodeDataModel
{
    Q_OBJECT

public:
    Vec4ConstVariableNode();

    // Serializable interface
public:
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject&) override;

    // NodeDataModel interface
public:
    QString
    caption() const override;

    QString
    portCaption( QtNodes::PortType portType
               , QtNodes::PortIndex portIndex ) const override;

    bool
    portCaptionVisible( QtNodes::PortType portType
                      , QtNodes::PortIndex portIndex ) const override;

    QString
    name() const override;

    unsigned int
    nPorts(QtNodes::PortType portType) const override;

    QtNodes::NodeDataType
    dataType( QtNodes::PortType portType
            , QtNodes::PortIndex portIndex ) const override;

    QWidget*
    embeddedWidget() override;

private:
    QWidget* _widget;
    std::array<QLineEdit*, 4> _editors;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif // CONSTVARIABLESNODES_HPP

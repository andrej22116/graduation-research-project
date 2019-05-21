#ifndef VARIABLEVALUECONTROLSFACTORY_HPP
#define VARIABLEVALUECONTROLSFACTORY_HPP

#include <QMap>

class VariableWidget;
class QWidget;

class VariableValueControlsFactory
{
    VariableValueControlsFactory();
    VariableValueControlsFactory(const VariableValueControlsFactory&) = default;
    VariableValueControlsFactory(VariableValueControlsFactory&&) = default;
    ~VariableValueControlsFactory() = default;
public:
    VariableValueControlsFactory& operator = (const VariableValueControlsFactory&) = delete;
    VariableValueControlsFactory& operator = (VariableValueControlsFactory&&) = delete;

    static VariableWidget* makeWidget( const QString& typeName
                                     , QWidget* parent = nullptr );

private:
    QMap<QString, std::function<VariableWidget* (QWidget*)>> _mapOfFactories;
};

#endif // VARIABLEVALUECONTROLSFACTORY_HPP

#include "FunctionAbsNodeModel.hpp"
#include "src/ShaderNodes/DoubleData"

using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::NodeValidationState;

FunctionAbsNodeModel::FunctionAbsNodeModel()
{
    _result = std::make_shared<DoubleData>(0);
}

QString FunctionAbsNodeModel::Name()
{
    return QString("FunctionAbsNodeModel");
}

QString FunctionAbsNodeModel::name() const
{
    return FunctionAbsNodeModel::Name();
}

unsigned int
FunctionAbsNodeModel::nPorts(QtNodes::PortType portType) const
{
    return 1;
}

NodeDataType
FunctionAbsNodeModel::dataType( PortType portType
                              , PortIndex portIndex ) const
{
    return DoubleData().type();
}

std::shared_ptr<NodeData>
FunctionAbsNodeModel::outData( PortIndex port )
{
    return std::static_pointer_cast<NodeData>(_result);
}

void
FunctionAbsNodeModel::setInData( std::shared_ptr<NodeData> data
                                    , PortIndex portIndex)
{
    _number = std::dynamic_pointer_cast<DoubleData>(data);
    emit modelUpdated();
}

QWidget*
FunctionAbsNodeModel::embeddedWidget()
{
    return nullptr;
}

QString
FunctionAbsNodeModel::caption() const
{
    return QStringLiteral("Abs");
}

bool FunctionAbsNodeModel::portCaptionVisible(QtNodes::PortType, QtNodes::PortIndex) const
{
    return true;
}

QString
FunctionAbsNodeModel::portCaption(PortType portType, PortIndex portIndex) const
{
    return test ? "Lol" : "Kek";//_result.get()->type().name;
}

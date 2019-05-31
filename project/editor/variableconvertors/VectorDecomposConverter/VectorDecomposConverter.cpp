#include "VectorDecomposConverter.hpp"

#include <ShaderNodeDataTypes.hpp>

QString
VectorDecomposConverter::
name() const
{
    return _name;
}


QString
VectorDecomposConverter::
caption() const
{
    return _caption;
}


unsigned int
VectorDecomposConverter::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 1
                                             : _vectorSize;
}


QtNodes::NodeDataType
VectorDecomposConverter::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex ) const
{
    if ( portType == QtNodes::PortType::In ) {
        return _dataType;
    }

    return FloatDataType{};
}


bool
VectorDecomposConverter::
portCaptionVisible( QtNodes::PortType portType
                  , QtNodes::PortIndex ) const
{
    return portType != QtNodes::PortType::In;
}


QString
VectorDecomposConverter::
portCaption( QtNodes::PortType
           , QtNodes::PortIndex portIndex ) const
{
    switch( portIndex ) {
        case 1: return "Red";
        case 2: return "Green";
        case 3: return "Blue";
        case 4: return "Alpha";
    }
}


QJsonObject
VectorDecomposConverter::
save() const
{
    return {};
}


VectorDecomposConverter::Factory
VectorDecomposConverter::
Vector2Factory()
{
    return s_vectorFactory(2);
}


VectorDecomposConverter::Factory
VectorDecomposConverter::
Vector3Factory()
{
    return s_vectorFactory(3);
}


VectorDecomposConverter::Factory
VectorDecomposConverter::
Vector4Factory()
{
    return s_vectorFactory(4);
}


void
VectorDecomposConverter::
build(uchar vectorSize)
{
    _vectorSize = vectorSize;
    _caption = QString("Vector%1 decomposition").arg(_vectorSize);
    _name = QString("Vec%1Decompos").arg(_vectorSize);

    switch ( _vectorSize ) {
    case 2: _dataType = Vec2DataType(); break;
    case 3: _dataType = Vec3DataType(); break;
    case 4: _dataType = Vec4DataType(); break;
    }
}


VectorDecomposConverter::Factory
VectorDecomposConverter::
s_vectorFactory(uchar vectorSize)
{
    return [vectorSize]() -> std::unique_ptr<NodeDataModel> {
        auto obj = std::make_unique<VectorDecomposConverter>();
        obj->build(vectorSize);

        return std::move(obj);
    };
}

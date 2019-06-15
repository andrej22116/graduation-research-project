#include "VectorConverterDataModel.hpp"
#include "VectorConverterWidget.hpp"

#include <ShaderNodeDataTypes.hpp>

QString
VectorConverterDataModel::
name() const
{
    return _name;
}


QString
VectorConverterDataModel::
caption() const
{
    return _caption;
}


unsigned int
VectorConverterDataModel::
nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 1 + _vectorSize
                                             : 1;
}


QtNodes::NodeDataType
VectorConverterDataModel::
dataType( QtNodes::PortType portType
        , QtNodes::PortIndex portIndex ) const
{
    if ( portIndex == 0 && portType == QtNodes::PortType::Out ) {
        return _dataType;
    }

    switch( portIndex ) {
    case 0: return NO_DATA_TYPE;
    default: return FloatDataType();
    }
}


bool
VectorConverterDataModel::
portCaptionVisible( QtNodes::PortType
                  , QtNodes::PortIndex portIndex ) const
{
    return portIndex > 0;
}


QString
VectorConverterDataModel::
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

QWidget*VectorConverterDataModel::embeddedWidget()
{
    return static_cast<QWidget*>(_converter);
}


QJsonObject
VectorConverterDataModel::
save() const
{
    auto obj = QtNodes::NodeDataModel::save();
    obj["convertor"] = _converter->save();
    return obj;
}


void
VectorConverterDataModel::
restore(const QJsonObject& object)
{
    _converter->restore(object);
}


VectorConverterDataModel::Factory
VectorConverterDataModel::
Vector2Factory()
{
    return s_vectorFactory(2);
}


VectorConverterDataModel::Factory
VectorConverterDataModel::
Vector3Factory()
{
    return s_vectorFactory(3);
}


VectorConverterDataModel::Factory
VectorConverterDataModel::
Vector4Factory()
{
    return s_vectorFactory(4);
}


void
VectorConverterDataModel::
build(uchar vectorSize)
{
    _vectorSize = vectorSize;
    _caption = QString("Vector%1 converter").arg(_vectorSize);
    _name = QString("Vec%1Converter").arg(_vectorSize);

    _converter = new VectorConverterWidget(_vectorSize);

    switch ( _vectorSize ) {
    case 2: _dataType = Vec2DataType(); break;
    case 3: _dataType = Vec3DataType(); break;
    case 4: _dataType = Vec4DataType(); break;
    }
}


VectorConverterDataModel::Factory
VectorConverterDataModel::
s_vectorFactory(uchar vectorSize)
{
    return [vectorSize]() -> std::unique_ptr<NodeDataModel> {
        auto convertor = std::make_unique<VectorConverterDataModel>();
        convertor->build(vectorSize);
        return std::move(convertor);
    };
}

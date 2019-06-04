#include "VectorConverterScene.hpp"

#include <QHash>
#include <QJsonValue>
#include "VectorPointGraphicsItem.hpp"
#include "VectorConnectGraphicsItem.hpp"

VectorConverterScene::
VectorConverterScene( uchar pointsCount
                    , QObject* parent )
    : QGraphicsScene(parent)
    , _pointsCount(pointsCount)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    PointValueType valueTypes[4] = { PointValueType::Red
                                   , PointValueType::Green
                                   , PointValueType::Blue
                                   , PointValueType::Alpha };

    qreal x = -36;
    for (auto type : {PointType::Input, PointType::Output}) {
        QPointF pointPos(x, -48);
        for (uchar i = 0; i < _pointsCount && i < 4; ++i) {

            auto point = new VectorPointGraphicsItem(valueTypes[i], type);
            point->setPos(pointPos);
            addItem(point);

            pointPos += {0, 24};

            if ( type == PointType::Input ) {
                connect( point
                       , &VectorPointGraphicsItem::onTryCreateNewConnect
                       , this
                       , &VectorConverterScene::onTryCreateConnect );

                _inputPoints += point;
            }
            else {
                _outputPoints += point;
            }

            _connectionsHash[point] = nullptr;
        }

        x = 36;
    }
}


void
VectorConverterScene::
onTryCreateConnect(VectorPointGraphicsItem* sender)
{
    auto connection = new VectorConnectGraphicsItem( this
                                                   , sender );
    addItem(connection);
    connection->grabMouse();

    prepareConnection(connection);
}


void
VectorConverterScene::
prepareConnection(VectorConnectGraphicsItem* connection)
{
    if ( connection->pointFrom() ) {
        _connectionsHash[connection->pointFrom()] = connection;
    }
    if ( connection->pointTo() ) {
        _connectionsHash[connection->pointTo()] = connection;
    }

    connect( connection
           , &VectorConnectGraphicsItem::beforeDestroy
           , this
           , [this](VectorConnectGraphicsItem* connection) {
        _connectionsHash[connection->pointFrom()] = nullptr;
        if ( connection->pointTo() ) {
            _connectionsHash[connection->pointTo()] = nullptr;
        }
    });

    connect( connection
           , &VectorConnectGraphicsItem::addConnection
           , this
           , [this](VectorConnectGraphicsItem* connection) {
        if ( _connectionsHash[connection->pointTo()] ) {
            this->removeItem(connection);
            delete connection;
            return;
        }
        _connectionsHash[connection->pointTo()] = connection;
    });
}


QJsonObject
VectorConverterScene::
save() const
{
    auto valueType2Leter = [](PointValueType type) {
        switch( type ) {
            case PointValueType::Red: return 'r';
            case PointValueType::Green: return 'g';
            case PointValueType::Blue: return 'b';
            case PointValueType::Alpha: return 'a';
        }
    };

    QString res;
    res.reserve(_pointsCount * 3);

    for ( auto& point : _outputPoints ) {
        auto connection = _connectionsHash[point];
        if ( connection ) {
            res += valueType2Leter(point->pointValueType());
            res += valueType2Leter(connection->pointFrom()->pointValueType());
        }
        else {
            auto leter = valueType2Leter(point->pointValueType());
            res += leter;
            res += leter;
        }
    }

    return {
        {"conversion", res}
    };
}


void
VectorConverterScene::
restore(const QJsonObject& object)
{
    auto value = object["conversion"];

    if ( !value.isString() ) { return; }

    auto string = value.toString("");
    if ( string.length() % 2 != 0 ) {
        return;
    }

    auto leterToPointPointer = [this]
                               (PointType type, QChar leter)
                               -> VectorPointGraphicsItem* {
        int index = -1;

        switch( leter.toLatin1() ) {
            case 'r': index = 0; break;
            case 'g': index = 1; break;
            case 'b': index = 2; break;
            case 'a': index = 3; break;
            default: return nullptr;
        }

        return type == PointType::Input ? _inputPoints[index]
                                        : _outputPoints[index];
    };

    for ( int i = 0, size = string.length(); i < size; ++i ) {
        auto out = leterToPointPointer(PointType::Output, string[i]);
        auto in = leterToPointPointer(PointType::Input, string[++i]);

        if ( !in || !out ) {
            continue;
        }

        auto connection = new VectorConnectGraphicsItem( this
                                                       , in
                                                       , out );

        addItem(connection);
        prepareConnection(connection);
    }
}

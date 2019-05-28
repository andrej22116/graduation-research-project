#ifndef VECTORCONVERTERSCENE_HPP
#define VECTORCONVERTERSCENE_HPP

#include <QGraphicsScene>
#include <QHash>
#include <QSet>

class VectorPointGraphicsItem;
class VectorConnectGraphicsItem;

class VectorConverterScene : public QGraphicsScene
{
    Q_OBJECT

public:
    VectorConverterScene( uchar pointsCount
                        , QObject* parent = nullptr );

    /**
     * @brief toJson generate convert string line
     * whit conversions /component to component/component to component/.../
     * @return QJsonValue with convert string
     */
    QJsonValue
    toJson();

protected slots:
    void
    onTryCreateConnect(VectorPointGraphicsItem* sender);

private:
    using ConnectionsHash = QHash< VectorPointGraphicsItem*
                                 , VectorConnectGraphicsItem* >;
    using OutputPointsSet = QSet<VectorPointGraphicsItem*>;

    uchar _pointsCount;
    ConnectionsHash _connectionsHash;
    OutputPointsSet _outputPoints;

};

#endif // VECTORCONVERTERSCENE_HPP

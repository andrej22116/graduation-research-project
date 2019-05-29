#ifndef VECTORCONVERTERSCENE_HPP
#define VECTORCONVERTERSCENE_HPP

#include <QGraphicsScene>
#include <QHash>
#include <QVector>
#include <nodes/internal/Serializable.hpp>

class VectorPointGraphicsItem;
class VectorConnectGraphicsItem;

class VectorConverterScene : public QGraphicsScene
                           , public QtNodes::Serializable
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
    QJsonObject
    save() const override;

    void
    restore(const QJsonObject& object) override;

protected slots:
    void
    onTryCreateConnect(VectorPointGraphicsItem* sender);

private:
    void
    prepareConnection(VectorConnectGraphicsItem* connection);

private:
    using ConnectionsHash = QHash< VectorPointGraphicsItem*
                                 , VectorConnectGraphicsItem* >;
    using PointsVector = QVector<VectorPointGraphicsItem*>;

    uchar _pointsCount;
    ConnectionsHash _connectionsHash;
    PointsVector _inputPoints;
    PointsVector _outputPoints;
};

#endif // VECTORCONVERTERSCENE_HPP

#ifndef LOOKCENTRALOBJECTCAMERA_HPP
#define LOOKCENTRALOBJECTCAMERA_HPP

#include "ICamera.hpp"

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class LookCentralObjectCamera : public QObject
                              , public ICamera
{
    Q_OBJECT
    //Q_INTERFACES(ICamera)

public:
    explicit LookCentralObjectCamera();
    ~LookCentralObjectCamera() override = default;

    // ICamera interface
public:
    const QVector3D& position() const override;

    const QVector3D& direction() const override;

    const QMatrix4x4& viewMatrix() const override;

    const QVector3D& up() const override;

public slots:
    void setUp(const QVector3D& up) override;

    void setPosition(const QVector3D& position) override;

    void move(const QVector3D& direction) override;

    void setDirection(const QVector3D& direction) override;

    void turn(const QVector3D& angles) override;

private:
    void calculateView();

private:
    QVector3D _position;
    QVector3D _direction;
    QVector3D _up;

    QVector3D _rotationAngles;
    QQuaternion _rotation;

    QMatrix4x4 _view;
};

#endif // LOOKCENTRALOBJECTCAMERA_HPP

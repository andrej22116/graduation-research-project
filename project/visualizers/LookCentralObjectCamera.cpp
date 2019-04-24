#include "LookCentralObjectCamera.hpp"

LookCentralObjectCamera::LookCentralObjectCamera() :
    _position(0, 0, 0),
    _direction(0, 0, 1),
    _up(0, 1, 0),
    _rotationAngles(0, 0, 0)
{
    calculateView();
}

const QVector3D& LookCentralObjectCamera::position() const
{
    return _position;
}

const QVector3D& LookCentralObjectCamera::direction() const
{
    return _direction;
}

const QMatrix4x4& LookCentralObjectCamera::viewMatrix() const
{
    return _view;
}

const QVector3D&LookCentralObjectCamera::up() const
{
    return _up;
}

void LookCentralObjectCamera::setUp(const QVector3D& up)
{
    _up = up.normalized();
}

void LookCentralObjectCamera::setPosition(const QVector3D& position)
{
    _position = position;

    calculateView();
}

void LookCentralObjectCamera::move(const QVector3D& direction)
{
    _direction += direction;

    if ( _direction.x() < 0 ) { _direction.setX(0); }
    if ( _direction.y() < 0 ) { _direction.setY(0); }
    if ( _direction.z() < 0 ) { _direction.setZ(0); }

    calculateView();
}

void LookCentralObjectCamera::setDirection(const QVector3D& direction)
{
    _direction = direction.normalized();
    calculateView();
}

void LookCentralObjectCamera::turn(const QVector3D& angles)
{
    _rotationAngles += angles;
    _rotation = QQuaternion::fromAxisAndAngle(_up, 90)
              * QQuaternion::fromAxisAndAngle({0, 1, 0}, _rotationAngles.y())
              * QQuaternion::fromAxisAndAngle({1, 0, 0}, _rotationAngles.x());

    calculateView();
}

void LookCentralObjectCamera::calculateView()
{
    _view.setToIdentity();
    _view.lookAt( _rotation * (_position + _direction)
                , _position
                , {0, 1, 0});

}

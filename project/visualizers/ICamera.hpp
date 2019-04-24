#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include <QObject>

class ICamera
{
public:
    ICamera() = default;
    virtual ~ICamera() = default;

    /// Return camera position vector
    virtual const QVector3D& position() const  = 0;

    /// Return camera look direction vector
    virtual const QVector3D& direction() const  = 0;

    /// Return view matrix
    virtual const QMatrix4x4& viewMatrix() const  = 0;

    /// Return camera up
    virtual const QVector3D& up() const = 0;

public slots:
    /// Hard set camera up
    virtual void setUp(const QVector3D& up) = 0;

    /// Hard set camera position
    virtual void setPosition(const QVector3D& position)  = 0;

    /// Add direction vector to camera position vector.
    virtual void move(const QVector3D& direction)  = 0;

    /// Hard set camera direction
    virtual void setDirection(const QVector3D& direction)  = 0;

    /// Add direction vector to camera direction vector.
    virtual void turn(const QVector3D& angles) = 0;
};

//Q_DECLARE_INTERFACE(ICamera, "ICamera")

#endif // ICAMERA_HPP

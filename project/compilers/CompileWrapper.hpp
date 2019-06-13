#ifndef COMPILEWRAPPER_HPP
#define COMPILEWRAPPER_HPP

#include <QObject>

class CompileWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CompileWrapper(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMPILEWRAPPER_HPP
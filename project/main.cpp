#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include "Application.hpp"

int main(int argc, char** argv) {
    //QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication application(argc, argv);

    Application thisApplication(application);

    return application.exec();
}

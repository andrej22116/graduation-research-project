#include "CompilerController.hpp"
#include <QApplication>
#include <QDebug>

int main(int argc, char** argv)
{
    CompilerController controller;
    QApplication app(argc, argv);

    controller.connect( &controller
                      , &CompilerController::compileChangeState
                      , &controller
                      , [](int val, const QString& msg) {
        qDebug() << "[" << val << "] " << msg;
    });

    controller.connect( &controller
                      , &CompilerController::compileComplete
                      , &controller
                      , [&](const QString& msg) {
        app.quit();
    });

    controller.compile("", nullptr);

    return app.exec();
}

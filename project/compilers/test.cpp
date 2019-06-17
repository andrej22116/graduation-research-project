#include "CompilerController.hpp"
#include <QApplication>
#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

int main(int argc, char** argv)
{
    CompilerController controller;
    QApplication app(argc, argv);

    QFile file("test.sdsln");
    file.open(QFile::ReadOnly);

    auto jsonDoc = QJsonDocument::fromJson(file.readAll());
    auto json = std::make_shared<QJsonObject>(jsonDoc.object());

    file.close();

    controller.connect( &controller
                      , &CompilerController::compileChangeState
                      , &controller
                      , [&](int val, const QString& msg) {
        qDebug() << "[" << val << "] " << msg;
    });

    controller.connect( &controller
                      , &CompilerController::compileComplete
                      , &controller
                      , [&](const QString& shaderText) {
        qDebug() << "[COMPLETE]";

        QFile file("fragment.glsl");
        file.open(QFile::WriteOnly);

        QTextStream stream(&file);
        stream << shaderText;

        file.close();

        app.quit();
    });

    controller.compile("", json);

    return app.exec();
}

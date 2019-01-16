#include <QWidget>
#include <QVBoxLayout>
#include <QApplication>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

int main(int argc, char** argv) {
    QApplication application(argc, argv);

    /*
    auto widget = new QWidget();
    widget->show();
    */

    FlowScene scene(nullptr);

    FlowView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return application.exec();
}

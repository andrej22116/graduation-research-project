#include <QWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QSurfaceFormat>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <editor/FunctionalNodes.hpp>

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

    QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto reg = std::make_shared<DataModelRegistry>();

    reg->registerModel<AdderFunctionalNode>();
    reg->registerModel<SubtractorFunctionalNode>();
    //reg->registerModel<DoubleNodeModel<PortType::In>>();
    //reg->registerModel<DoubleNodeModel<PortType::Out>>();

    ConnectionStyle::setConnectionStyle(
        R"(
      {
        "ConnectionStyle": {
          "UseDataDefinedColors": true
        }
      }
      )");

    FlowScene scene(reg);
    FlowView view(&scene);


    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return application.exec();
}

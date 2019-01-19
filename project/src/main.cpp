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

#include "src/ShaderNodes/Model/Functions/ClassFunctionAbsNodeModel/FunctionAbsNodeModel.hpp"
#include "src/ShaderNodes/DoubleNodeModel"

int main(int argc, char** argv) {
    QApplication application(argc, argv);

    /*
    auto widget = new QWidget();
    widget->show();
    */

    auto reg = std::make_shared<DataModelRegistry>();

    reg->registerModel<FunctionAbsNodeModel>();
    reg->registerModel<DoubleNodeModel<PortType::In>>();
    reg->registerModel<DoubleNodeModel<PortType::Out>>();

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

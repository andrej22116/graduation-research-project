/*
#include <QMainWindow>
#include <QDockWidget>
#include <QApplication>
#include <QSurfaceFormat>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>
#include <nodes/Node>

#include <editor/FunctionalNodes.hpp>
#include <editor/nodesstore/NodeWidget.hpp>

//#include <editor/nodesstore/NodesStoreWidget.hpp>
#include <editor/nodesstore/FlowLayout.hpp>
#include <editor/EditorGraphicsScene.hpp>
#include <editor/VariableNodes.hpp>

#include <QScrollArea>
#include <QSplitter>

#include <visualizers/LookCentralObjectCamera.hpp>
#include <visualizers/OpenGLScene.hpp>
#include <visualizers/TargetSceneWrapperWidget.hpp>
#include <QDebug>

#include <editor/nodesstore/NodeStoreWidget.hpp>
#include <editor/variableconvertors/VectorConveroter/VectorConverterDataModel.hpp>
#include <editor/variableconvertors/VectorDecomposConverter/VectorDecomposConverter.hpp>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
*/

#include <QApplication>
#include "Application.hpp"

int main(int argc, char** argv) {
    QApplication application(argc, argv);

    Application thisApplication(application);

    /*
    auto widget = new QWidget();
    widget->show();
    */
    /*
    QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto reg = std::make_shared<DataModelRegistry>();

    reg->registerModel<AdderFunctionalNode>("Math");
    reg->registerModel<SubtractorFunctionalNode>("Math");

    reg->registerModel<ConditionFunctionalNode>("Logick");

    reg->registerModel<RadiansFunctionalNode>("Trigonometry");
    reg->registerModel<DegreesFunctionalNode>("Trigonometry");
    reg->registerModel<SinFunctionalNode>("Trigonometry");
    reg->registerModel<CosFunctionalNode>("Trigonometry");
    reg->registerModel<TanFunctionalNode>("Trigonometry");
    reg->registerModel<CtanFunctionalNode>("Trigonometry");
    reg->registerModel<ArcSinFunctionalNode>("Trigonometry");
    reg->registerModel<ArcCosFunctionalNode>("Trigonometry");
    reg->registerModel<ArcTanFunctionalNode>("Trigonometry");
    reg->registerModel<PowFunctionalNode>("Exponential");
    reg->registerModel<ExpFunctionalNode>("Exponential");
    reg->registerModel<Exp2FunctionalNode>("Exponential");
    reg->registerModel<LogFunctionalNode>("Exponential");
    reg->registerModel<Log2FunctionalNode>("Exponential");
    reg->registerModel<SqrtFunctionalNode>("Exponential");
    reg->registerModel<InverseSqrtFunctionalNode>("Exponential");
    reg->registerModel<ConstUserVariableNode>("SuperTest");
    reg->registerModel<UserVariableNode>("SuperTest");
    reg->registerModel<VectorConverterDataModel>( VectorConverterDataModel::Vector2Factory()
                                                , "Convertors" );
    reg->registerModel<VectorConverterDataModel>( VectorConverterDataModel::Vector3Factory()
                                                , "Convertors" );
    reg->registerModel<VectorConverterDataModel>( VectorConverterDataModel::Vector4Factory()
                                                , "Convertors" );
    /*reg->registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector2Factory()
                                               , "Convertors" );
    reg->registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector3Factory()
                                               , "Convertors" );
    reg->registerModel<VectorDecomposConverter>( VectorDecomposConverter::Vector4Factory()
                                               , "Convertors" );*/
    //reg->registerModel<DoubleNodeModel<PortType::In>>();
    //reg->registerModel<DoubleNodeModel<PortType::Out>>();

    /*
    ConnectionStyle::setConnectionStyle(
    R"(
      {
        "ConnectionStyle": {
          "UseDataDefinedColors": true
        }
      }
      )");

    auto mainWindow = new QMainWindow{};
    mainWindow->setDockOptions( QMainWindow::AllowTabbedDocks
                              | QMainWindow::AllowNestedDocks
                              | QMainWindow::VerticalTabs
                              | QMainWindow::GroupedDragging );

    mainWindow->setWindowIcon(QIcon(":/images/icons/Icon.png"));

    EditorGraphicsScene scene(reg);
    FlowView view(&scene, mainWindow);

    QSizePolicy sizePolicy;
    sizePolicy.setVerticalPolicy(QSizePolicy::Policy::Minimum);
    sizePolicy.setHorizontalPolicy(QSizePolicy::Policy::Minimum);

    auto dock = new QDockWidget("Shader editor", mainWindow);
    dock->setSizePolicy(sizePolicy);
    dock->setWidget(&view);
    dock->setAllowedAreas(Qt::DockWidgetArea::AllDockWidgetAreas);
    mainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dock);

    auto nodeStore = new NodeStoreWidget(reg, mainWindow);
    dock = new QDockWidget("Nodes store", mainWindow);
    dock->setSizePolicy(sizePolicy);
    dock->setWidget(nodeStore);
    dock->setAllowedAreas(Qt::DockWidgetArea::AllDockWidgetAreas);
    mainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dock);

    mainWindow->setWindowTitle("Node-based flow editor");
    mainWindow->resize(800, 600);
    mainWindow->show();

    LookCentralObjectCamera camera;
    camera.setDirection({0, 0, 1});

    qDebug() << "Camera direction: " << camera.direction();

    camera.move({0, 1, 0});

    qDebug() << "Camera direction: " << camera.direction();
    qDebug() << "Camera position: " << camera.position();

    camera.setDirection({0, 0, 0});

    qDebug() << "Camera direction: " << camera.direction();
    qDebug() << "Camera position: " << camera.position();

    TargetSceneWrapperWidget ogls( std::make_shared<OpenGLScene>() );
    ogls.showNormal();

    mainWindow->setStyleSheet("QWidget{background-color: rgb(60, 60, 65); color: white;}");

    */

    return application.exec();
}

#include "OpenGLScene.hpp"

#include "TargetObject.hpp"
#include "LookCentralObjectCamera.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_4_0_Core>
#include <QFile>
#include <QTextStream>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QTimer>

OpenGLScene::OpenGLScene(QWidget* parent) :
    QOpenGLWidget(parent),
    _targetObjectVboId(QOpenGLBuffer::VertexBuffer),
    _targetObjectEboId(QOpenGLBuffer::IndexBuffer),
    _matrixUniformLocation(0),
    _timer(std::make_shared<QTimer>(this)),
    _camera(std::make_shared<LookCentralObjectCamera>()),
    _cameraMoves(false)
{
    QSurfaceFormat format;
    format.setVersion(4, 2);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::NoProfile);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    setFormat(format);

    _timer->setInterval(1000 / 60);
    _timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect( _timer.get(), &QTimer::timeout
           , this, &OpenGLScene::update );
    _timer->start();
    //_renderPipeLine.push_back(&OpenGLScene::renderTargetObject);
}

OpenGLScene::~OpenGLScene()
{
}


void OpenGLScene::setSceneProperties(QJsonDocument& jsonProperties)
{
}


void OpenGLScene::setVertexShaderText(const QString& text)
{
    if ( _vertexShader ) {
        _userShaderProgramm.removeShader(_vertexShader.get());
    }

    _vertexShader = std::make_shared<QOpenGLShader>(QOpenGLShader::Vertex);
    if ( !_vertexShader->compileSourceCode(text) ) {
        throw std::runtime_error(_vertexShader->log().toStdString());
    }

    _userShaderProgramm.addShader(_vertexShader.get());
}

void OpenGLScene::setGeometryShaderText(const QString& text)
{
    if ( _geometryShader ) {
        _userShaderProgramm.removeShader(_geometryShader.get());
    }

    _geometryShader = std::make_shared<QOpenGLShader>(QOpenGLShader::Geometry);
    if ( !_geometryShader->compileSourceCode(text) ) {
        throw std::runtime_error(_geometryShader->log().toStdString());
    }

    _userShaderProgramm.addShader(_geometryShader.get());
}

void OpenGLScene::setFragmentShaderText(const QString& text)
{
    if ( _fragmentShader ) {
        _userShaderProgramm.removeShader(_fragmentShader.get());
    }

    _fragmentShader = std::make_shared<QOpenGLShader>(QOpenGLShader::Fragment);
    if ( !_fragmentShader->compileSourceCode(text) ) {
        throw std::runtime_error(_fragmentShader->log().toStdString());
    }

    _userShaderProgramm.addShader(_fragmentShader.get());
}

void OpenGLScene::compileShader()
{
    _userShaderProgramm.link();

    _matrixUniformLocation = _userShaderProgramm.uniformLocation("resultTransformMatrix");

    trySetRenderPipline();
}

void OpenGLScene::setVariableValue(const QString& variableName, const QVariant& value)
{
}

void OpenGLScene::deleteVariableValue(const QString& variableName)
{
}

void OpenGLScene::setUseCursorPosition(bool useCursorPosition)
{
}

void OpenGLScene::setUseTime(bool useTime)
{
}

void OpenGLScene::setTexture(const QString& name, const QPixmap& texture)
{
}

void OpenGLScene::setTargetObject(std::shared_ptr<TargetObject> object)
{
    auto glf = QOpenGLContext::currentContext()->functions();
    _targetObject = object;

    _targetObjectVaoId.destroy();
    _targetObjectVboId.destroy();
    _targetObjectEboId.destroy();

    _targetObjectVaoId.create();
    _targetObjectVboId.create();
    _targetObjectEboId.create();

    _targetObjectVaoId.bind();
    _targetObjectVboId.bind();
    _targetObjectEboId.bind();

    int vboSize = static_cast<int>(_targetObject->vertices.size())
                * static_cast<int>(sizeof(Vertex));
    int eboSize = static_cast<int>(_targetObject->indices.size())
                * static_cast<int>(sizeof(uint));

    _targetObjectVboId.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    _targetObjectVboId.allocate(vboSize);
    _targetObjectVboId.write(0, _targetObject->vertices.data(), vboSize);

    _targetObjectEboId.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    _targetObjectEboId.allocate(eboSize);
    _targetObjectEboId.write(0, _targetObject->indices.data(), eboSize);

    glf->glEnableVertexAttribArray(0);
    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    _targetObjectVaoId.release();
    _targetObjectVboId.release();
    _targetObjectEboId.release();

    trySetRenderPipline();
}

void OpenGLScene::setCubeMapTexture(const QPixmap& texture)
{
}

void OpenGLScene::setLight(std::shared_ptr<LightSource> lightSource)
{
}

std::shared_ptr<QPixmap> OpenGLScene::renderObjectToImage(const QSize& size)
{
    QOpenGLFramebufferObject imageBuffer(size);
    imageBuffer.bind();

    auto glf4 = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_0_Core>();

    glf4->glViewport(0, 0, size.width(), size.height());
    resizeGL(size.width(), size.height());

    glf4->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    renderTargetObject();

    glf4->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glf4->glViewport(0, 0, this->width(), this->height());
    resizeGL(this->width(), this->height());

    imageBuffer.bindDefault();

    return std::make_shared<QPixmap>(QPixmap::fromImage(imageBuffer.toImage()));
}

void OpenGLScene::render()
{
    auto data = _renderPipeLine.data();
    for ( size_t i = 0, size = _renderPipeLine.size(); i < size; ++i, ++data ) {
        (*data)(this);
    }
}

void OpenGLScene::update()
{
    QOpenGLWidget::update();
}

void OpenGLScene::initializeGL()
{
    auto glf = QOpenGLContext::currentContext()->functions();

    glf->glClearColor(0, 0.2f, 0.1f, 1.0f);

    loadVertexShader();
    setFragmentShaderText("#version 420 core\n"
                          "out vec4 FragColor;\n"
                          "void main() {\n"
                          "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                          "} ");
    compileShader();
}

void OpenGLScene::resizeGL(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = height > 0 ? static_cast<float>(height) : 1;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45.0f , fWidth / fHeight , 0.1f, 1000.0f);

    calculateResultMatrix();

}

void OpenGLScene::paintGL()
{
    auto glf = QOpenGLContext::currentContext()->functions();

    glf->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    render();
}

void OpenGLScene::mousePressEvent(QMouseEvent* event)
{
    _cameraMoves = true;
    _lastCursorPosition = event->pos();
}

void OpenGLScene::mouseReleaseEvent(QMouseEvent* event)
{
    _cameraMoves = false;
}

void OpenGLScene::mouseMoveEvent(QMouseEvent* event)
{
    if ( !_cameraMoves ) { return; }

    auto newCursorPosition = event->pos();

    _camera->turn(QVector3D( newCursorPosition.y() - _lastCursorPosition.y()
                           , _lastCursorPosition.x() - newCursorPosition.x()
                           , 0 ));

    _lastCursorPosition = newCursorPosition;

    calculateResultMatrix();
    update();
}

void OpenGLScene::wheelEvent(QWheelEvent* event)
{
    _camera->move({ 0, 0, (event->delta() > 0) ? (-1.0f) : (1.0f) });

    calculateResultMatrix();
    update();
}

void OpenGLScene::trySetRenderPipline()
{
    if ( !_userShaderProgramm.isLinked() ) { return; }
    if ( !_targetObject || !*_targetObject ) { return; }

    setRenderPipline();
}

void OpenGLScene::setRenderPipline()
{
    _renderPipeLine.clear();

    _renderPipeLine.push_back(&OpenGLScene::renderTargetObject);
}

void OpenGLScene::calculateResultMatrix()
{
    _resultMatrix = _projectionMatrix * _camera->viewMatrix();
}

void OpenGLScene::loadVertexShader()
{
    QFile vertexShadeFiler(":/shaders/vertex_base.glsl");
    if ( !vertexShadeFiler.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "Erororoeroeorweor";
    }
    QTextStream stream(&vertexShadeFiler);
    QString vertexShaderText = stream.readAll();
    vertexShadeFiler.close();

    setVertexShaderText(vertexShaderText);
}

void OpenGLScene::rebuildBuffers()
{

}

void OpenGLScene::renderTargetObject()
{
    auto glf = QOpenGLContext::currentContext()->functions();

    _userShaderProgramm.bind();
    _targetObjectVaoId.bind();

    _userShaderProgramm.setUniformValue(_matrixUniformLocation, _resultMatrix);

    glf->glDrawElements( GL_TRIANGLES
                       , static_cast<int>(_targetObject->indices.size())
                       , GL_UNSIGNED_INT
                       , nullptr);

    _targetObjectVaoId.release();
    _userShaderProgramm.release();
}

void OpenGLScene::renderBackground()
{

}

void OpenGLScene::renderServiceInfo()
{

}

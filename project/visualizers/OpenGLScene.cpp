#include "OpenGLScene.hpp"

#include "TargetObject.hpp"
#include "LookCentralObjectCamera.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions_4_2_Core>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QTimer>

#ifdef QT_DEBUG
void showOpenGLErrors(const QString& file, int line) {
    auto glf = QOpenGLContext::currentContext()->functions();
    GLenum err ( glf->glGetError() );

    while ( err != GL_NO_ERROR )
    {
        QString error;
        switch ( err )
        {
            case GL_INVALID_OPERATION:  error="GL_INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:       error="GL_INVALID_ENUM";           break;
            case GL_INVALID_VALUE:      error="GL_INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:      error="GL_OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }
        qDebug() << error << " - " << file << ":" << line;
        err = glf->glGetError();
    }
}
#   define D_showOpenGLErrors(file, line) showOpenGLErrors((file), (line));
#else
#   define D_showOpenGLErrors(file, line)
#endif

#include <QLabel>
#include <QGridLayout>

OpenGLScene::
OpenGLScene(QWidget* parent)
    : QOpenGLWidget(parent)
    , _targetObjectVboId(QOpenGLBuffer::VertexBuffer)
    , _targetObjectEboId(QOpenGLBuffer::IndexBuffer)
    //, _differedShadingBuffer(1, 1)
    , _matrixUniformLocation(0)
    , _timer(std::make_shared<QTimer>(this))
    , _camera(std::make_shared<LookCentralObjectCamera>())
    , _cameraMoves(false)
{
    _timer->setInterval(1000 / 60);
    _timer->setTimerType(Qt::TimerType::PreciseTimer);

    _testWidget = new QWidget();
    _testWidgetLabel = new QLabel(_testWidget);
    auto layout = new QGridLayout(_testWidget);
    _testWidget->setLayout(layout);
    layout->addWidget(_testWidgetLabel);
    //_testWidget->show();
}

OpenGLScene::
~OpenGLScene()
{
    delete _testWidget;
}


void
OpenGLScene::
setSceneProperties(QJsonDocument& jsonProperties)
{
}


void
OpenGLScene::
setVertexShaderText(const QString& text)
{
    _vertexShaderText = text;
}


void
OpenGLScene::
setGeometryShaderText(const QString& text)
{
    _geometryShaderText = text;
}


void
OpenGLScene::
setFragmentShaderText(const QString& text)
{
    _fragmentShaderText = text;
}


void
OpenGLScene::
compileShader()
{
    makeCurrent();

    _userShaderProgramm = std::make_shared<QOpenGLShaderProgram>();

    auto vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    //auto geometryShader = new QOpenGLShader(QOpenGLShader::Geometry, this);
    auto fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);

    vertexShader->compileSourceCode(_vertexShaderText);
    //geometryShader->compileSourceCode(_geometryShaderText);
    fragmentShader->compileSourceCode(_fragmentShaderText);

    _userShaderProgramm->addShader(vertexShader);
    //_userShaderProgramm->addShader(geometryShader);
    _userShaderProgramm->addShader(fragmentShader);

    _userShaderProgramm->link();

    _matrixUniformLocation = _userShaderProgramm->uniformLocation("resultTransformMatrix");

    trySetRenderPipline();
}


void
OpenGLScene::
setVariableValue( const QString& variableName
                , const QVariant& value )
{
}


void
OpenGLScene::
deleteVariableValue(const QString& variableName)
{
}


void
OpenGLScene::
setUseCursorPosition(bool useCursorPosition)
{
}


void
OpenGLScene::setUseTime(bool useTime)
{
}


void
OpenGLScene::
setTexture(const QString& name, const QPixmap& texture)
{
}


void
OpenGLScene::
setTargetObject(std::shared_ptr<TargetObject> object)
{
    this->makeCurrent();

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
    _targetObjectVboId.allocate(_targetObject->vertices.data(), vboSize);

    _targetObjectEboId.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    _targetObjectEboId.allocate(_targetObject->indices.data(), eboSize);

    glf->glEnableVertexAttribArray(0);

    glf->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    _targetObjectVaoId.release();

    trySetRenderPipline();

    this->doneCurrent();
}


void
OpenGLScene::
setCubeMapTexture(const QPixmap& texture)
{
}


void
OpenGLScene::
setLight(std::shared_ptr<LightSource> lightSource)
{
}


std::shared_ptr<QPixmap>
OpenGLScene::
renderObjectToImage(const QSize& size)
{
    QOpenGLFramebufferObject imageBuffer(size);
    imageBuffer.bind();

    auto glf4 = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_2_Core>();

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


QWidget*
OpenGLScene::
widget()
{
    return this;
}


void
OpenGLScene::
render()
{
    update();
}


void
OpenGLScene::
initializeGL()
{
    auto glf = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_2_Core>();

    glf->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    if ( _targetObject ) { setTargetObject(_targetObject); }

    loadVertexShader();
    setFragmentShaderText("#version 420 core\n"
                          "out vec4 FragColor;\n"
                          "void main() {\n"
                          "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                          "} ");
    compileShader();

    //createDsBuffer();
}


void
OpenGLScene::
resizeGL(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = height > 0 ? static_cast<float>(height) : 1;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45.0f , fWidth / fHeight , 0.1f, 1000.0f);

    calculateResultMatrix();

}


void
OpenGLScene::
paintGL()
{
    auto glf = QOpenGLContext::currentContext()->functions();

    glf->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    auto data = _renderPipeLine.data();
    for ( size_t i = 0, size = _renderPipeLine.size(); i < size; ++i, ++data ) {
        (*data)(this);
    }
}


void
OpenGLScene::
mousePressEvent(QMouseEvent* event)
{
    if ( event->button() == Qt::MouseButton::RightButton ) {
        auto targetObject = std::make_shared<TargetObject>();
        targetObject->loadMesh("test.obj");

        setTargetObject(targetObject);
        return;
    }
    _cameraMoves = true;
    _lastCursorPosition = event->pos();
}


void
OpenGLScene::
mouseReleaseEvent(QMouseEvent* event)
{
    _cameraMoves = false;
}


void
OpenGLScene::
mouseMoveEvent(QMouseEvent* event)
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


void
OpenGLScene::
wheelEvent(QWheelEvent* event)
{
    _camera->move({ 0, 0, (event->delta() > 0) ? (-1.0f) : (1.0f) });

    calculateResultMatrix();
    update();
}


void
OpenGLScene::
trySetRenderPipline()
{
    if ( _userShaderProgramm && !_userShaderProgramm->isLinked() ) { return; }
    if ( !_targetObject || !*_targetObject ) { return; }

    setRenderPipline();
}


void
OpenGLScene::
setRenderPipline()
{
    _renderPipeLine.clear();

    _renderPipeLine.push_back(&OpenGLScene::renderTargetObject);
}


void
OpenGLScene::
calculateResultMatrix()
{
    _resultMatrix = _projectionMatrix * _camera->viewMatrix();
}


void
OpenGLScene::
loadVertexShader()
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


void
OpenGLScene::
rebuildBuffers()
{

}


void
OpenGLScene::
renderTargetObject()
{
    auto glf = QOpenGLContext::currentContext()->functions();

    _userShaderProgramm->bind();
    D_showOpenGLErrors("OpenGLScene.cpp", 366);

    _userShaderProgramm->setUniformValue(_matrixUniformLocation, _resultMatrix);
    D_showOpenGLErrors("OpenGLScene.cpp", 369);

    _targetObjectVaoId.bind();
    D_showOpenGLErrors("OpenGLScene.cpp", 372);

    //_differedShadingBuffer->bind();
    glf->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glf->glDrawElements( GL_TRIANGLES
                       , static_cast<int>(_targetObject->indices.size())
                       , GL_UNSIGNED_INT
                       , nullptr );
    D_showOpenGLErrors("OpenGLScene.cpp", 378);

    //_differedShadingBuffer->release();
    //_testWidgetLabel->setPixmap(QPixmap::fromImage(_differedShadingBuffer->toImage()));

    _targetObjectVaoId.release();

    _userShaderProgramm->release();
}


void
OpenGLScene::
renderSsao()
{
    auto glf = QOpenGLContext::currentContext()->functions();

}


void
OpenGLScene::
renderBackground()
{

}


void
OpenGLScene::
renderServiceInfo()
{

}


void
OpenGLScene::
createDsBuffer()
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);

    _differedShadingBuffer = std::make_shared<QOpenGLFramebufferObject>(800, 600, format);
    //_differedShadingBuffer->addColorAttachment(this->size(), GL_RGB16F);
    //_differedShadingBuffer->addColorAttachment(this->size(), GL_RGB16F);
    //_differedShadingBuffer->addColorAttachment(this->size());
}


void
OpenGLScene::
createLppBuffer()
{

}

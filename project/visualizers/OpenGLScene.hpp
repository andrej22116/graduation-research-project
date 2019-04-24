#ifndef OPENGLSCENE_HPP
#define OPENGLSCENE_HPP

#include "ITargetSceneRenderer.hpp"

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <QMap>
#include <vector>

#include <functional>


class QTimer;
class QOpenGLShaderProgram;
class ICamera;

class OpenGLScene : public QOpenGLWidget
                  , public ITargetSceneRenderer
{
    Q_OBJECT

public:
    OpenGLScene(QWidget* parent = nullptr);
    ~OpenGLScene() override;

    // ITargetSceneRenderer interface
public:
    void setSceneProperties(QJsonDocument& jsonProperties) override;

    void setVertexShaderText(const QString& text) override;

    void setGeometryShaderText(const QString& text) override;

    void setFragmentShaderText(const QString& text) override;

    void compileShader() override;

    void setVariableValue( const QString& variableName
                         , const QVariant& value ) override;

    void deleteVariableValue(const QString& variableName) override;

    void setUseCursorPosition(bool useCursorPosition) override;

    void setUseTime(bool useTime) override;

    void setTexture(const QString& name, const QPixmap& texture) override;

    void setTargetObject(std::shared_ptr<TargetObject> object) override;

    void setCubeMapTexture(const QPixmap& texture) override;

    void setLight(std::shared_ptr<LightSource> lightSource) override;

    std::shared_ptr<QPixmap> renderObjectToImage(const QSize& size) override;

public slots:
    void render() override;

private slots:
    void update();

    // QOpenGLWidget interface
protected:
    void initializeGL() override;

    void resizeGL(int width, int height) override;

    void paintGL() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

private:
    void trySetRenderPipline();

    void setRenderPipline();

    void calculateResultMatrix();

    void loadVertexShader();

    void rebuildBuffers();

    void renderTargetObject();

    void renderBackground();

    void renderServiceInfo();

private: /// Buffers OpenGL -- Unused!
    //GLuint _bufferIdAlbedo;
    //GLuint _bufferIdNormals;
    //GLuint _bufferIdPosition;
    //GLuint _bufferIdDepth;

private: /// Shaders
    //QOpenGLShaderProgram _globalShader;
    QOpenGLShaderProgram _userShaderProgramm;
    std::shared_ptr<QOpenGLShader> _vertexShader;
    std::shared_ptr<QOpenGLShader> _geometryShader;
    std::shared_ptr<QOpenGLShader> _fragmentShader;

private: /// Params and sources
    QMap<QString, GLuint> _textures;
    QMap<QString, QVariant> _variables;

private: /// Target object sources
    std::shared_ptr<TargetObject> _targetObject;
    QOpenGLVertexArrayObject _targetObjectVaoId;
    QOpenGLBuffer _targetObjectVboId;
    QOpenGLBuffer _targetObjectEboId;

private: /// Rendering
    /**
     * @brief Used for set rendere function call order
     */
    std::vector<std::function<void(OpenGLScene*)>> _renderPipeLine;

private: /// Transformation
    int _matrixUniformLocation;
    QMatrix4x4 _projectionMatrix;
    QMatrix4x4 _resultMatrix;

private: /// Scene
    std::shared_ptr<QTimer> _timer;
    std::shared_ptr<ICamera> _camera;
    bool _cameraMoves;
    QPoint _lastCursorPosition;
};

#endif // OPENGLSCENE_HPP

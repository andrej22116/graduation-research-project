#ifndef ITARGETSCENERENDERER_HPP
#define ITARGETSCENERENDERER_HPP

#include <QObject>
#include <memory>

struct TargetObject;
struct LightSource;

/**
 * @brief The ITargetSceneRenderer class is the interface for use render target
 */
class ITargetSceneRenderer : public virtual QObject
{
    Q_OBJECT

public:
    /**
     * @brief Set render properties
     * @param json document with properties
     */
    virtual void setSceneProperties(QJsonDocument& jsonProperties) = 0;

    /**
     * @brief setVertexShaderText
     * @param text - vertex shader programm text;
     */
    virtual void setVertexShaderText(const QString& text) = 0;

    /**
     * @brief setGeometryShaderText
     * @param text - geometry shader programm text;
     */
    virtual void setGeometryShaderText(const QString& text) = 0;

    /**
     * @brief setPixelShaderText
     * @param text - pixel shader programm text;
     */
    virtual void setPixelShaderText(const QString& text) = 0;

    /**
     * @brief Compile and setup shader programm
     */
    virtual void compileShader() = 0;

    /**
     * @brief Set variable value for use in shader runtime
     * @param variableName - name of variable in shader programm
     * @param value - variable value
     */
    virtual void setVariableValue( const QString& variableName
                                 , const QVariant& value ) = 0;

    /**
     * @brief Delete variable value to not use it
     * @param variableName - name of variable
     */
    virtual void deleteVariableValue(const QString& variableName) = 0;

    /**
     * @brief Specifies whether to pass the cursor
     * position to the shader
     * @param useCursorPosition - true, if need pass the cursor position
     */
    virtual void setUseCursorPosition(bool useCursorPosition) = 0;

    /**
     * @brief Specifies whether to pass the time to the shader
     * @param useTime - true, if need pass the time
     */
    virtual void setUseTime(bool useTime) = 0;

    /**
     * @brief Set texture for use in shader
     * @param name - texture variable name on the shader
     * @param texture
     */
    virtual void setTexture( const QString& name
                           , const QPixmap& texture) = 0;

    virtual void setTargetObject(std::shared_ptr<TargetObject> object) = 0;

    /**
     * @brief Set cubemap texture to the scene
     * @param texture of the scene cube
     */
    virtual void setCubeMapTexture(const QPixmap& texture) = 0;

    /**
     * @brief Set light source in the scene
     * @param lightSource - pointer to lightSource
     */
    virtual void setLight(std::shared_ptr<LightSource> lightSource) = 0;

public slots:
    /**
     * @brief Rendering scene
     */
    virtual void render() = 0;

};

#endif // ITARGETSCENERENDERER_HPP

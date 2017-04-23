#include "modelviewer.h"
#include "model.h"
#include <QtWidgets>
#include <QtOpenGL>

/**
 * @brief Default constructor, initialises variables to default values
 * @param parent Widget's parent (default: nullptr)
 */
ModelViewer::ModelViewer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setBackgroundColour(cBackgroundColourDefault);
    setForegroundColour(cForegroundColourDefault);
    setPointSize(cPointSizeDefault);
    setZoomAmount(cZoomAmountDefault);
    setRenderMode(cRenderModeDefault);
}

/**
 * @brief Sets the ModelViewer's Model
 * @param model New model
 */
void ModelViewer::setModel(const Model& model)
{
    mModel = model;
    setZoomAmount(cZoomAmountDefault);
}

/**
 * @brief Returns a reference to the ModelViewer's Model
 * @return Reference to the ModelViewer's model
 */
Model &ModelViewer::model()
{
    return mModel;
}

/**
 * @brief Sets the ModelViewer's background colour
 * @param colour New colour
 */
void ModelViewer::setBackgroundColour(const QColor& colour)
{
    mBackgroundColour = colour;
}

/**
 * @brief Returns the ModelViewer's background colour
 * @return ModelViewer's background colour
 */
QColor ModelViewer::backgroundColour() const
{
    return mBackgroundColour;
}

/**
 * @brief Sets the ModelViewer's foreground colour
 * @param colour New colour
 */
void ModelViewer::setForegroundColour(const QColor& colour)
{
    mForegroundColour = colour;
}

/**
 * @brief Returns the ModelViewer's foreground colour
 * @return ModelViewer's foreground colour
 */
QColor ModelViewer::foregroundColour() const
{
    return mForegroundColour;
}

/**
 * @brief Sets the ModelViewer's point size
 * @param pointSize New point size
 */
void ModelViewer::setPointSize(const GLfloat& pointSize)
{
    mPointSize = pointSize;
}

/**
 * @brief Sets the ModelViewer's zoom amount
 * @param zoomAmount New zoom amount
 */
void ModelViewer::setZoomAmount(const GLfloat& zoomAmount)
{
    mZoomAmount = zoomAmount;
}

/**
 * @brief Returns the ModelViewer's zoom amount
 * @return ModelViewer's zoom amount
 */
GLfloat ModelViewer::zoomAmount() const
{
    return mZoomAmount;
}

/**
 * @brief Sets the ModelViewer's render mode
 * @param renderMode new render mode
 */
void ModelViewer::setRenderMode(const ModelViewer::RenderMode &renderMode)
{
    mRenderMode = renderMode;
}

/**
 * @brief Returns the ModelViewer's render mode
 * @return ModelViewer's render mode
 */
ModelViewer::RenderMode ModelViewer::renderMode()
{
    return mRenderMode;
}

/**
 * @brief Initialises OpenGL (called once, before the first ModelViewer::paintGL call)
 */
void ModelViewer::initializeGL()
{
    glEnable(GL_DEPTH_CLAMP);
}

/**
 * @brief Paints the ModelViewer (called whenever the Widget needs to be painted)
 */
void ModelViewer::paintGL()
{
    glClearColor(mBackgroundColour.red() / 255.0f, BackgroundColour.green(), mBackgroundColour.blue() / 255.0f, mBackgroundColour.alpha();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-mZoomAmount, mZoomAmount, -mZoomAmount, mZoomAmount, cNear, cFar);

    if(!mModel.isLoaded())
    {
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(mModel.position().x(), mModel.position().y(), mModel.position().z());

    glRotatef(mModel.rotation().x(), 1.0f, 0.0f, 0.0f);
    glRotated(mModel.rotation().y(), 0.0f, 1.0f, 0.0f);
    glRotated(mModel.rotation().z(), 0.0f, 0.0f, 1.0f);

    glPointSize(mPointSize);
    glColor3f(mForegroundColour.red() / 255.0f, mForegroundColour.green() / 255.0f, mForegroundColour.blue() / 255.0f);

    const QVector<QVector3D>& cVertices = mModel.vertices();
    glBegin(mRenderMode == ePointCloud ? GL_POINTS : GL_LINES);
        for(int i = 0; i < cVertices.size(); ++i)
            glVertex3f(cVertices[i].x(), cVertices[i].y(), cVertices[i].z());
    glEnd();
}

/**
 * @brief Handles resizing of the ModelViewer Widget
 * @param width New width
 * @param height New height
 */
void ModelViewer::resizeGL(int width, int height)
{
    glViewport(0, (height - width) / 2, width, width);
}

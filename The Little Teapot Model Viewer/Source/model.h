#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QVector>
#include <vector>

/**
 * @brief Model class
 */
class Model
{

public:

    /* Default constructor that initialises values */
    Model();

    /* Parses a Waterfront OBJ file and extracts vertex data. */
    bool loadFromFile(const QString& filePath);

    /* Sets the Model's position */
    void setPosition(const QVector3D& position);

    /* Returns the Model's position */
    QVector3D position() const;

    /* Sets the Model's rotation */
    void setRotation(const QVector3D& rotation);

    /* Returns the Model's rotation */
    QVector3D rotation() const;

    /* Returns the Model's vertices */
    const QVector<QVector3D>& vertices() const;

    /* Returns the amount of vertices the Model has */
    int vertexCount() const;

    /* Returns true if the Model has at least one vertex */
    bool isLoaded() const;

private:

    /* Model's default position */
    static const QVector3D cPositionDefault;

    /* Model's default rotation */
    static const QVector3D cRotationDefault;

    /* Model's position */
    QVector3D mPosition;

    /* Model's rotation */
    QVector3D mRotation;

    /* Collection of Vertices obtained through Model::loadFromFile */
    QVector<QVector3D> mVertices;

};

#endif // MODEL_H

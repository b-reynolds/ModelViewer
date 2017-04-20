#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

const QVector3D Model::cPositionDefault = QVector3D(0.0f, 0.0f, 0.0f);
const QVector3D Model::cRotationDefault = QVector3D(0.0f, 0.0f, 0.0f);

/**
 * @brief Default constructor, initialises variables to their default values
 */
Model::Model()
{
    mPosition = QVector3D(0.0f, 0.0f, 0.0f);
    mRotation = QVector3D(0.0f, 0.0f, 0.0f);
}

/**
 * @brief Parses a Waterfront OBJ file and extracts vertex data
 * @param filePath File path
 * @return True if at least one vertex was read
 */
bool Model::loadFromFile(const QString &filePath)
{
    mVertices.clear();

    QFile inputFile(filePath);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error: Failed to open file" << filePath;
        return false;
    }

    qDebug() << "Info: Opened file (" << filePath << ").";

    QTextStream inputStream(&inputFile);
    int lineNumber = -1;

    while(!inputStream.atEnd())
    {
        QString currentLine = inputStream.readLine();
        QStringList lineSegments = currentLine.split(" ", QString::SkipEmptyParts);
        lineNumber++;

        if(lineSegments.isEmpty())
        {
            qDebug() << "Info: Line " << lineNumber << " is empty";
            continue;
        }

        QString keyword = lineSegments.front();
        lineSegments.pop_front();

        if(keyword != "v")
        {
            qDebug() << "Info: Line does not contain keyword \"v\" (" << lineNumber << ")";
            continue;
        }

        if(lineSegments.size() < 3)
        {
            qDebug() << "Info: Line does not contain expected number of values \"v\" (" << lineNumber << ")";
            continue;
        }

        bool conversionSuccessful = false;
        float values[3];

        for(unsigned int i = 0; i < 3; ++i)
        {
            values[i] = lineSegments.front().toFloat(&conversionSuccessful);
            lineSegments.pop_front();

            if(!conversionSuccessful)
            {
                break;
            }
        }

        if(!conversionSuccessful)
        {
            qDebug() << "Error: Failed to convert value (" << lineNumber << ")";
            continue;
        }

        mVertices.push_back(QVector3D(values[0], values[1], values[2]));
        qDebug() << "Info: Line proccessed succesfully (" << lineNumber << ")";
    }

    inputFile.close();
    qDebug() << "Info: Closed file" << filePath;

    setPosition(cPositionDefault);
    setRotation(cRotationDefault);

    return (mVertices.size() > 0);
}

/**
 * @brief Sets the Model's position
 * @param position new position
 */
void Model::setPosition(const QVector3D& position)
{
    mPosition = position;
    qDebug() << "Info: Set Model's position to " << mPosition;
}

/**
 * @brief Returns the Model's position
 * @return QVector3D containing the Model's position
 */
QVector3D Model::position() const
{
    return mPosition;
}

/**
 * @brief Sets the Model's rotation
 * @param rotation new rotation
 */
void Model::setRotation(const QVector3D& rotation)
{
    mRotation = rotation;
    qDebug() << "Info: Set Model's rotation to " << mRotation;
}

/**
 * @brief Returns the Model's rotation
 * @return QVector3D containing the Model's position
 */
QVector3D Model::rotation() const
{
    return mRotation;
}

/**
 * @brief Returns the Model's vertices
 * @return Constant reference to the QVector3D that contains the Model's vertices
 */
const QVector<QVector3D>& Model::vertices() const
{
    return mVertices;
}

/**
 * @brief Returns the amount of vertices the model has
 * @return The amount of vertices the model has
 */
int Model::vertexCount() const
{
    return mVertices.size();
}

/**
 * @brief Returns true if the Model has at least one vertex
 * @return True if the Model has at least one vertex
 */
bool Model::isLoaded() const
{
    return (mVertices.size() > 0);
}

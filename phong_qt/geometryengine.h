#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    float x(int i, int j);

    float y(int i, int j);


   float z(int i, int j);

private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
   // QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H

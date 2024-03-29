#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector4D>
#include <eigen/Eigen/Dense>
#include "obj_loader.h"
#include "pca.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
     GeometryEngine(obj_loader &obj);
    virtual ~GeometryEngine();

     int toss_index=0;
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void drawObjGeometry(QOpenGLShaderProgram *program);

    void drawObjArray(QOpenGLShaderProgram *program);
    QVector3D getNormal(QVector4D a, QVector4D b, QVector4D c);
    QVector3D getNormal_vertex(QVector4D a, QVector4D b, QVector4D c);
    float x(int i, int j);
    float y(int i, int j);
   float z(int i, int j);
   int normalFlag=0;
   int scaleAll=0;
   QVector3D transtlateAvg;

    void initCubeGeometry();
    void initObj();
     obj_loader *objLoader;
     obj_loader *objLoaders_toss[26];
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer arrayObjBuf[26];
    QOpenGLBuffer indexObjBuf;
    void calculatePCA();
};

#endif // GEOMETRYENGINE_H

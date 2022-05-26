#ifndef MYTORUS_H
#define MYTORUS_H


#include <QVector4D>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <qopenglextrafunctions.h>


struct MyTorusVertex
{
    QVector4D position;
    QVector4D color;
    QVector3D normal;
};

class MyTorus
{
public:
    MyTorus(void);
    ~MyTorus(void);

    int NumVertices;

    MyTorusVertex* Vertices;
    float x(int i, int j);

    float y(int i, int j);


    float z(int i, int j);
    QVector3D getNormal(QVector4D a, QVector4D b, QVector4D c);
    GLuint Init();//(int la_slice, int lo_slice, vec4 color = vec4(0.5, 0.5, 0.5, 1));
    void SetPositionAndOtherAttributes(QOpenGLShaderProgram *program);

    GLuint vao;
    GLuint buffer;
    bool bInitialized;

    void Draw(QOpenGLShaderProgram *program);
};
#endif // MYTORUS_H

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector4D position;
    //QVector4D color;
};

#define PI 3.1415926535898
#define R 0.8
#define r 0.5


#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

#define DEF_D 10

static int p = 40;
static int q = 40;
 int  NumVertices=0;

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]
float GeometryEngine::x(int i, int j)
{
    return ((R + r * cos((-1 + 2 * (float)j / q) * PI)) * cos((-1 + 2 * (float)i / p) * PI));
}

float GeometryEngine::y(int i, int j)
{
    return ((R + r * cos((-1 + 2 * (float)j / q) * PI)) * sin((-1 + 2 * (float)i / p) * PI));
}

float GeometryEngine::z(int i, int j)
{
    return (r * sin((-1 + 2 * (float)j / q) * PI));
}

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
   NumVertices = 100000;
   //QVector4D color= QVector4D(1,0,0,0);
   VertexData  *vertices = new VertexData[NumVertices];

        int cur = 0;
            for (int j = 0; j <= p; j++)
            {
                for (int i= 0; i <= q; i++)
                {
                    QVector4D a(x(i, j), y(i, j), z(i, j),1);
                    QVector4D b(x(i, j+1), y(i, j+1), z(i, j+1),1);
                    QVector4D c(x(i+1, j+1), y(i+1, j+1), z(i+1, j+1),1);
                    QVector4D d(x(i+1, j), y(i+1, j), z(i+1, j),1);


                    if (j != p)
                    {
                        vertices[cur].position = a;     cur++;
                        vertices[cur].position = b;       cur++;
                        vertices[cur].position = c;    cur++;
                    }
                    if (j != 0)
                    {
                        vertices[cur].position = c;       cur++;
                        vertices[cur].position = d;     cur++;
                        vertices[cur].position = a;      cur++;
                    }
                }
            }

 NumVertices=cur;
//! [1]
    // Transfer vertex data to VBO 0

    arrayBuf.bind();
    arrayBuf.allocate(vertices, NumVertices * sizeof(VertexData));


//! [1]
}
//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
  //  indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(VertexData));




    // Offset for texture coordinate
    //offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
   // int texcoordLocation = program->attributeLocation("a_texcoord");
   // program->enableAttributeArray(texcoordLocation);
   // program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
   // glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_SHORT, nullptr);
     glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}
//! [2]

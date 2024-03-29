
#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

#define PI 3.1415926535898
#define R 0.8
#define r 0.5


#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

#define DEF_D 10

static int p = 40;
static int q = 40;

struct VertexData
{
    QVector4D position;
    QVector4D color;
      QVector4D normal;
  //  QVector2D texCoord;
};

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
   int  NumVertices = 100000;
   QVector4D color= QVector4D(1,0,0,0);
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


                        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = a;  cur++;

                        vertices[cur].position = b;   vertices[cur].color = color; vertices[cur].normal = b;   cur++;
                        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = c; cur++;
                    }
                    if (j != 0)
                    {


                        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = c;  cur++;
                        vertices[cur].position = d;   vertices[cur].color = color; vertices[cur].normal = d;  cur++;
                        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = a;  cur++;
                    }
                }
            }


    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, cur * sizeof(VertexData));


//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();


    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("vPosition");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector4D);

    int vColor = program->attributeLocation("vColor");
    program->enableAttributeArray(vColor);
    program->setAttributeBuffer(vColor, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector4D);

    int vNormal = program->attributeLocation("vNormal");
    program->enableAttributeArray(vNormal);
    program->setAttributeBuffer(vNormal, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
   // int texcoordLocation = program->attributeLocation("a_texcoord");
   // program->enableAttributeArray(texcoordLocation);
   // program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    //여기 ㅁㅗ르겟음
    glDrawElements(GL_TRIANGLES, 100000, GL_UNSIGNED_SHORT, nullptr);
}
//! [2]

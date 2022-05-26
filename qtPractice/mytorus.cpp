#include "mytorus.h"
//#include <QOpenGLFunctions_3_3_Core>
#include <math.h>

#define PI 3.1415926535898
#define R 0.8
#define r 0.5


#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

#define DEF_D 10

static int p = 40;
static int q = 40;

MyTorus::MyTorus(void)
{
    bInitialized = false;
    NumVertices = 0;
    Vertices = NULL;
}

MyTorus::~MyTorus(void)
{
    if (Vertices != NULL)
        delete[] Vertices;
}

/*
QVector3D MyTorus::getNormal(QVector4D a, QVector4D b, QVector4D c)
{
    QVector3D a3 = QVector3D(a.x(), a.y(), a.z());
    QVector3D b3 = QVector3D(b.x(), b.y(), b.z());
    QVector3D c3 = QVector3D(c.x(), c.y(), c.z());
    QVector3D p = a3 - b3;
    QVector3D q = c3 - b3;

    QVector3D n = normalize(cross(p, q));

    return n;
}
*/
float MyTorus::x(int i, int j)
{
    return ((R + r * cos((-1 + 2 * (float)j / q) * PI)) * cos((-1 + 2 * (float)i / p) * PI));
}

float MyTorus::y(int i, int j)
{
    return ((R + r * cos((-1 + 2 * (float)j / q) * PI)) * sin((-1 + 2 * (float)i / p) * PI));
}

float MyTorus::z(int i, int j)
{
    return (r * sin((-1 + 2 * (float)j / q) * PI));
}

GLuint MyTorus::Init()
{
    // The Cube should be initialized only once;
    if (bInitialized == true) return vao;

    NumVertices = (p - 2) * q * 2 * 3 + 2 * p * 3*10;
    Vertices = new MyTorusVertex[NumVertices];
    QVector4D color = QVector4D(0.5, 0.5, 0.5,1);
    int cur = 0;
    for (int j = 0; j <= p; j++)
    {
        for (int i = 0; i <= q; i++)
        {
            QVector4D a(x(i, j), y(i, j), z(i, j),1);
            QVector4D b(x(i, j + 1), y(i, j + 1), z(i, j + 1),1);
            QVector4D c(x(i + 1, j + 1), y(i + 1, j + 1), z(i + 1, j + 1),1);
            QVector4D d(x(i + 1, j), y(i + 1, j), z(i + 1, j),1);


            if (j != p)
            {


                Vertices[cur].position = a;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)a;  cur++;

                Vertices[cur].position = b;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)b; cur++;
                Vertices[cur].position = c;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)c; cur++;
            }
            if (j != 0)
            {


                Vertices[cur].position = c;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)c;  cur++;
                Vertices[cur].position = d;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)d;  cur++;
                Vertices[cur].position = a;   Vertices[cur].color = color; Vertices[cur].normal = (QVector3D)a;   cur++;
            }
        }
    }


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MyTorusVertex) * NumVertices, Vertices, GL_STATIC_DRAW);

    bInitialized = true;
    return vao;
}

void MyTorus::SetPositionAndOtherAttributes(QOpenGLShaderProgram *program)
{

    int vPosition = program->attributeLocation("vPosition");
       program->enableAttributeArray(vPosition);
       program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 4, sizeof(MyTorusVertex));

       int vColor = program->attributeLocation("vColor");
          program->enableAttributeArray(vColor);
          program->setAttributeBuffer(vColor, GL_FLOAT, sizeof(QVector4D), 4, sizeof(MyTorusVertex));


    int vNormal = program->attributeLocation("vNormal");
       program->enableAttributeArray(vNormal);
       program->setAttributeBuffer(vNormal, GL_FLOAT, sizeof(QVector4D)+ sizeof(QVector4D), 3, sizeof(MyTorusVertex));




}

void MyTorus::Draw(QOpenGLShaderProgram *program)
{
    if (!bInitialized) return;         // check whether it is initiazed or not.

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    SetPositionAndOtherAttributes(program);

    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

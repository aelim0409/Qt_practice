#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <stdlib.h>


struct VertexData
{
    QVector4D position;
    QVector4D color;
    QVector4D normal;
};

#define PI 3.1415926535898
#define R 0.8
#define r 0.5

#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

#define DEF_D 10

static int p = 100;
static int q = 100;
 int  NumVertices=0;

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    arrayObjBuf.create();
    indexObjBuf.create();
    objLoader= new obj_loader();

    // Initializes cube geometry and transfers it to VBOs
    QString name;

    for(int i=1;i<=26;i++)
    {
         qDebug()<<"ddddd" <<i;
        objLoaders_toss[i-1]=new obj_loader();
        if(i<10)
            name="0"+QString::number(i)+".obj";
        else
          name=QString::number(i)+".obj";
        objLoaders_toss[i-1]->loadModel("C:/homework3/toss/"+name);
        objLoaders_toss[i-1]->fileName=name;


        objLoader=objLoaders_toss[i-1];
        initObj();
      //  Sleep(500);


    }

}

GeometryEngine::GeometryEngine(obj_loader &obj)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    arrayObjBuf.create();
    indexObjBuf.create();
    objLoader= new obj_loader();

    // Initializes cube geometry and transfers it to VBOs
    QString name;

    for(int i=1;i<=26;i++)
    {
         qDebug()<<"ddddd" <<i;
        objLoaders_toss[i-1]=new obj_loader();
        if(i<10)
            name="0"+QString::number(i)+".obj";
        else
          name=QString::number(i)+".obj";
        objLoaders_toss[i-1]->loadModel("C:/homework3/toss/"+name);
        objLoaders_toss[i-1]->fileName=name;
/*
      objLoader=objLoaders_toss[i-1];
        initObj();
        Sleep(1000);
*/
    }

}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    arrayObjBuf.destroy();
    indexObjBuf.destroy();
}
//! [0]
//!
//!
QVector3D GeometryEngine::getNormal(QVector4D a, QVector4D b, QVector4D c)
{

    QVector3D a3 = QVector3D(a.x(), a.y(), a.z());
    QVector3D b3 = QVector3D(b.x(), b.y(), b.z());
        QVector3D c3 = QVector3D(c.x(), c.y(), c.z());
        QVector3D p = a3 - b3;
        QVector3D q = c3 - b3;

    QVector3D n = n.crossProduct(p,q);
     n.normalize();
     return n;

}

QVector3D GeometryEngine::getNormal_vertex(QVector4D a, QVector4D b, QVector4D c)
{

    QVector3D a3 = QVector3D(a.x(), a.y(), a.z());
    QVector3D b3 = QVector3D(b.x(), b.y(), b.z());
        QVector3D c3 = QVector3D(c.x(), c.y(), c.z());
        QVector3D p = a3+b3+c3;
        p=p/3;


     return p;

}

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

void GeometryEngine::initObj()
{
    QString name;
    qDebug()<<"objName:"<<objLoader->fileName;

   // scanf_s("obj Name : %s",&name );
   //name="buddha.obj";
  //name="25.obj";

    qDebug()<<objLoader->vertex_num<<" "<<objLoader->m_triangles.size();



    //objLoader->loadModel("C:/homework3/"+name);
   // objLoader->loadModel("C:/homework3/toss/"+name);


    scaleAll = objLoader->scaleAll;
    transtlateAvg=QVector3D(-objLoader->avgX,-objLoader->avgY,-(objLoader->avgZ)-5);

    QVector4D color= QVector4D(0.5,0.5,0.5,0);
    NumVertices = objLoader->m_triangles.size()*3;
    VertexData  *vertices = new VertexData[NumVertices];


    int cur=0;

    QVector3D * fnormal = new QVector3D[objLoader->m_triangles.size()];
    for(int i=0;i<objLoader->m_triangles.size();i++)
    {
        QVector4D a = QVector4D(objLoader->m_triangles[i].p1,1);
        QVector4D b = QVector4D(objLoader->m_triangles[i].p2,1);
        QVector4D c = QVector4D(objLoader->m_triangles[i].p3,1);

        fnormal[i] = getNormal(a,b,c);
    }


    QVector3D * vnormal = new QVector3D[objLoader->vertex_num];
    for(int i=0; i<objLoader->vertex_num; i++)
        vnormal[i] =QVector3D(0,0,0);




    for(int i=0;i<objLoader->m_triangles.size();i++)
    {
        //for(int j=0;j<3;j++);
        vnormal[objLoader->m_triangles[i].v1]+=fnormal[i];
        vnormal[objLoader->m_triangles[i].v2]+=fnormal[i];
        vnormal[objLoader->m_triangles[i].v3]+=fnormal[i];
    }

    for(int i=0; i<objLoader->vertex_num; i++)
        vnormal[i].normalize();

    qDebug()<<"vnormal calculate finish";



    cur=0;
/*
    for(int i=0;i<objLoader->m_triangles.size();i++)
    {
        QVector4D a = QVector4D(objLoader->m_triangles[i].p1,1);
        QVector4D b = QVector4D(objLoader->m_triangles[i].p2,1);
        QVector4D c = QVector4D(objLoader->m_triangles[i].p3,1);

        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = QVector4D(fnormal[i],1);    cur++;
        vertices[cur].position = b;   vertices[cur].color = color; vertices[cur].normal = QVector4D(fnormal[i],1);    cur++;
        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = QVector4D(fnormal[i],1);    cur++;
    }
*/
    for(int i=0;i<objLoader->m_triangles.size();i++)
    {
        QVector4D a = QVector4D(objLoader->m_triangles[i].p1,1);
        QVector4D b = QVector4D(objLoader->m_triangles[i].p2,1);
        QVector4D c = QVector4D(objLoader->m_triangles[i].p3,1);

        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = QVector4D(vnormal[objLoader->m_triangles[i].v1],1);    cur++;
        vertices[cur].position = b;   vertices[cur].color = color; vertices[cur].normal = QVector4D(vnormal[objLoader->m_triangles[i].v2],1);    cur++;
        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = QVector4D(vnormal[objLoader->m_triangles[i].v3],1);    cur++;
    }


    arrayObjBuf.bind();
    arrayObjBuf.allocate(vertices, NumVertices * sizeof(VertexData));

    delete [] fnormal;
    delete [] vnormal;
}


void GeometryEngine::drawObjGeometry(QOpenGLShaderProgram *program)
{
//    for(int i=0;i<26;i++)
  //  {
      //  objLoader=objLoaders_toss[i];
      //  initObj();
    // Tell OpenGL which VBOs to use
    arrayObjBuf.bind();
  //  indexBuf.bind();



    // Tell OpenGL programmable pipeline how to locate vertex position data
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vPosition = program->attributeLocation("vPosition");
    printf("vPosition = %d\n",vPosition);
    program->enableAttributeArray(vPosition);
    program->setAttributeBuffer(vPosition, GL_FLOAT, offset, 4, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector4D);
    int vColor = program->attributeLocation("vColor");
     printf("vColor = %d\n",vColor);
    program->enableAttributeArray(vColor);
    program->setAttributeBuffer(vColor, GL_FLOAT, offset, 4, sizeof(VertexData));

    offset += sizeof(QVector4D);
    int vNormal = program->attributeLocation("vNormal");
    printf("vNormal = %d\n",vNormal);
    program->enableAttributeArray(vNormal);
    program->setAttributeBuffer(vNormal, GL_FLOAT, offset, 4, sizeof(VertexData));


     glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    // arrayObjBuf.destroy();
   //   Sleep(500);
   // }
}

void GeometryEngine::drawObjArray(QOpenGLShaderProgram *program)
{
    initObj();
    drawObjGeometry(program);
}
void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
   NumVertices = 100000000;
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

/*
                    if (j != p)
                    {
                        vertices[cur].position = a;        cur++;
                        vertices[cur].position = b;    cur++;
                        vertices[cur].position = c;        cur++;
                    }
                    if (j != 0)
                    {
                        vertices[cur].position = c;     cur++;
                        vertices[cur].position = d;     cur++;
                        vertices[cur].position = a;     cur++;
                    }
                    */
                    if (j != p)
                    {
                        QVector4D n = QVector4D(getNormal(a,b,c),1);
                        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
                        vertices[cur].position = b;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
                        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
                    }
                    if (j != 0)
                    {
                        QVector4D n = QVector4D(getNormal(c,d,a),1);
                        vertices[cur].position = c;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
                        vertices[cur].position = d;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
                        vertices[cur].position = a;   vertices[cur].color = color; vertices[cur].normal = n;    cur++;
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



    // Tell OpenGL programmable pipeline how to locate vertex position data
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vPosition = program->attributeLocation("vPosition");
    printf("vPosition = %d\n",vPosition);
    program->enableAttributeArray(vPosition);
    program->setAttributeBuffer(vPosition, GL_FLOAT, offset, 4, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector4D);
    int vColor = program->attributeLocation("vColor");
     printf("vColor = %d\n",vColor);
    program->enableAttributeArray(vColor);
    program->setAttributeBuffer(vColor, GL_FLOAT, offset, 4, sizeof(VertexData));

    offset += sizeof(QVector4D);
    int vNormal = program->attributeLocation("vNormal");
    printf("vNormal = %d\n",vNormal);
    program->enableAttributeArray(vNormal);
    program->setAttributeBuffer(vNormal, GL_FLOAT, offset, 4, sizeof(VertexData));


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

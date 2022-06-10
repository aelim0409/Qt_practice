#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <QString>
#include <QVector3D>
#include <QList>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <qopenglfunctions_4_3_core.h>

class obj_loader
{
public:
    obj_loader();

    QString fileName;
    int vertex_num=0;
    int face_num=0;
    /*
    float maxX = 0,maxY=0,maxZ=0;
    float minX=-1000000, minY=-100000,minZ=-100000;
    float sumX=0,sumY=0,sumZ=0;
    float avgX,avgY,avgZ=0;
    float scaleX,scaleY,scaleZ=0;
    float scaleAll=0;
*/
       struct QOpenGLTriangle3D
       {
           QVector3D p1 = QVector3D(0, 0, 0);
           QVector3D p2 = QVector3D(0, 0, 0);
           QVector3D p3 = QVector3D(0, 0, 0);
           QVector3D p1Normal = QVector3D(0, 0, 0);
           QVector3D p2Normal = QVector3D(0, 0, 0);
           QVector3D p3Normal = QVector3D(0, 0, 0);

       };
       bool loaded;

       QVector<QOpenGLTriangle3D> m_triangles;

       QOpenGLTriangle3D triangle;

       QVector<QVector3D> v, vn;


       void loadModel(QString s);
     //  void drawObject();


};

#endif // OBJ_LOADER_H

#ifndef BIN_READER_H
#define BIN_READER_H

#include <QString>
#include <QVector3D>
#include <QList>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <qopenglfunctions_4_3_core.h>

class bin_reader
{
public:

     bin_reader();
     struct struct_info{
         QChar header[12];
         int version;
         int num_points;
         float startFrame;
         float sampleRate;
         int num_samples;
     };

     struct_info st_info;

     struct pos_xyz
     {
         float x;
         float y;
         float z;
     };


     //pos_xyz *positions;


     struct samples
     {
          QVector<pos_xyz> positions;
     };

     QVector<samples> sample;

    struct VertexData
    {
        QVector4D position;
        QVector4D color;
        QVector4D normal;
    };



    VertexData  *vertices;


    QString fileName;
    int vertex_num=0;
    int face_num=0;

    float maxX = 0,maxY=0,maxZ=0;
    float minX=-1000000, minY=-100000,minZ=-100000;
    float sumX=0,sumY=0,sumZ=0;
    float avgX,avgY,avgZ=0;
    float scaleX,scaleY,scaleZ=0;
    float scaleAll=0;

       struct QOpenGLTriangle3D
       {
           int v1,v2,v3=0;
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


       void loadModel(char* s);
     //  void drawObject();
};

#endif // OBJ_LOADER_H

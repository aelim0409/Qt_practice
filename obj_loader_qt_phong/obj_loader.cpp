#include "obj_loader.h"
#include <QFile>
#include <QDebug>
#include <QChar>

obj_loader::obj_loader()
{

}


void obj_loader::loadModel(QString s)
{
    QFile file(s);


    if(file.exists())
    {
         printf("file exists \n");
         if(file.open(QFile::ReadOnly | QFile::Text))
                  {
                      printf("File open \n");
                      // 마지막 줄까지 읽을 동안 반복
                      while(!file.atEnd())
                      {

  //                        qDebug() << "loop!";

                          QString line = file.readLine().trimmed();

                          QList<QString> lineParts = line.split(' ');

//                          qDebug() << "lineParts " << lineParts;

                          if(lineParts.count() > 0)
                          {

 //                             qDebug() << "lineparts first == " << lineParts.first();

                              if(lineParts.first() == "v")
                              {
 //                                 qDebug() << "lineparts first == 'v' ";

                                  v.push_back(QVector3D(lineParts.at(1).toFloat(), lineParts.at(2).toFloat(),
                                           lineParts.at(3).toFloat()));

                                  /*
                                  if(v[vertex_num].x()> maxX)   maxX=v[vertex_num].x();
                                  if(v[vertex_num].y()> maxY)   maxY=v[vertex_num].y();
                                  if(v[vertex_num].z()> maxZ)   maxZ=v[vertex_num].z();

                                  if(v[vertex_num].x() < minX)	minX=v[vertex_num].x();
                                  if(v[vertex_num].y() < minY)	minY=v[vertex_num].y();
                                  if(v[vertex_num].z() < minZ)	minZ=v[vertex_num].z();

                                  sumX += v[vertex_num].x();
                                  sumY +=v[vertex_num].y();
                                  sumZ += v[vertex_num].z();
*/


                                  vertex_num++;
                              }


                              else if(lineParts.first() == "f")
                              {
 //                                qDebug() << "lineparts first == 'f' ";

//                                 qDebug() << "v: " << v;
//                                 qDebug() << "p1 index" << lineParts.at(1).split("//").value(0).toInt() - 1;
                                // qDebug() << "p2 index" << lineParts.at(1).split("//").at(1);

//                                  triangle.p1 = v.at(lineParts.at(1).split("//").value(0).toInt() - 1);
 //                                 qDebug()<<"v.at(1)="<<lineParts.at(1).split("//").value(0).toInt() - 1;

//                                  triangle.p1 = v.at(lineParts.at(1).toInt() - 1);
//                                  triangle.p2 = v.at(lineParts.at(2).toInt() - 1);
//                                  triangle.p3 = v.at(lineParts.at(3).toInt() - 1);


                                  triangle.p1 = v[lineParts.at(1).toInt() - 1];
                                  triangle.p2 = v[lineParts.at(2).toInt() - 1];
                                  triangle.p3 = v[lineParts.at(3).toInt() - 1];


/*
                                  triangle.p2 = v.at(lineParts.at(2).split("//").at(0).toInt() - 1);
//                                  qDebug()<<"v.at(2)="<<lineParts.at(2).split("//").value(0).toInt() - 1;

                                  triangle.p3 = v.at(lineParts.at(3).split("//").at(0).toInt() - 1);
//                                  qDebug()<<"v.at(3)="<<lineParts.at(3).split("//").value(0).toInt() - 1;
//                                  qDebug() << "p1 found";qDebug() << "p2 found";

*/
                                  m_triangles.push_back(triangle);

                              //  qDebug() << "Triangles count" << m_triangles.count();
                                  /*
                                  for(int i=0; i<m_triangles.count();i++)
                                  {
                                      qDebug()<<m_triangles.at(i).p1.x()<<", "<<m_triangles.at(i).p1.y()<<", "
                                             <<m_triangles.at(i).p1.z();
                                      qDebug()<<m_triangles.at(i).p2.x()<<", "<<m_triangles.at(i).p2.y()<<", "
                                             <<m_triangles.at(i).p2.z();
                                      qDebug()<<m_triangles.at(i).p3.x()<<", "<<m_triangles.at(i).p3.y()<<", "
                                            <<m_triangles.at(i).p3.z();
                                  }
                                  */
                              }
                          }

                      }

                      qDebug() << "loop END!";
/*
                      avgX = sumX / vertex_num;
                       avgY = sumY / vertex_num;
                       avgZ = sumZ / vertex_num;

                       scaleX = (1.0-maxX)*10 + 1;
                       scaleY = (1.0-maxY)*10 + 1;
                       scaleZ = (1.0-maxZ)*10 + 1;

                       if(scaleX > scaleY)	{
                         if(scaleY > scaleZ)
                           scaleAll= scaleZ;
                         else
                           scaleAll= scaleY;
                       }

                       else if(scaleX <scaleY)	{
                         if(scaleX < scaleZ)
                           scaleAll = scaleX;
                         else
                           scaleAll= scaleZ;
                       }

                        qDebug() << scaleX;
                        */
                      file.close();
                  }
              }
    else
        qDebug()<<"No file!";
         }

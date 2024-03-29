#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>

#include "geometryengine.h"
#include "obj_loader.h"
#include "pca.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QProgressBar>
#include "ui_openglwidget.h"

class GeometryEngine;

QT_BEGIN_NAMESPACE
namespace Ui { class openglWidget; }
QT_END_NAMESPACE
/*
class openglWidget : public QWidget
{
    Q_OBJECT
public:
    openglWidget(QWidget *parent = nullptr);
    ~openglWidget();
private:
    Ui::openglWidget *ui;
};
*/


class openglWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    openglWidget(QWidget *parent = nullptr);
    using QOpenGLWidget::QOpenGLWidget;
    ~openglWidget();

    int normalFlag=0;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
    QProgressBar progress_bar;

private slots:
    //void on_pushButton_clicked();

   // void on_pushButton_2_clicked();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries = nullptr;
    pca pca;

    QOpenGLTexture *texture = nullptr;

  //  QMatrix4x4 projection;
    QMatrix4x4 ProjMat;
     QMatrix4x4 ViewMat;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
    QVector3D rot;
    obj_loader *objLoader2;
    obj_loader *objLoaders_toss2[26];

    Ui::openglWidget ui;

public slots:
    void ButtonClicked();
    void ButtonClicked_2();
     void ButtonClicked_3();
     void ButtonClicked_4();
      void ButtonClicked_5();
      void ButtonClicked_play();


};
#endif // OPENGLWIDGET_H

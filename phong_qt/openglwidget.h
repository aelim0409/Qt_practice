#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

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
    using QOpenGLWidget::QOpenGLWidget;
    ~openglWidget();



protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries = nullptr;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};
#endif // OPENGLWIDGET_H

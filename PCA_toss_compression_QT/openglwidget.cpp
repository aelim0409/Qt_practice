#include "openglwidget.h"
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include "ui_openglwidget.h"

float frameNum=23;
openglWidget::openglWidget(QWidget *par)
{
   // ui->setupUi(this);
   progress_bar.setMaximum(26);
   progress_bar.setMinimum(1);
   progress_bar.setOrientation(Qt::Horizontal);
   progress_bar.setGeometry(10,30,700,30);
   progress_bar.setVisible(true);
}
openglWidget::~openglWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
  //  makeCurrent();
    delete texture;
    delete geometries;
    //doneCurrent();
}
float mytime=0;
//! [0]
void openglWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
    qDebug()<< "space!";
}

void openglWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void openglWidget::KeyPressEvent(QKeyEvent *e)
{
        if(e->key()==Qt::Key_Space)
        {
            geometries->normalFlag=1;
            qDebug()<< "space!";
        }

}
//! [0]

//! [1]
void openglWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;
    mytime+=1;
    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
//! [1]

void openglWidget::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    //initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]
/*
    QString name;

    for(int i=1;i<=26;i++)
    {
         qDebug()<<"ddddd" <<i;
        objLoaders_toss2[i-1]=new obj_loader();
        if(i<10)
            name="0"+QString::number(i)+".obj";
        else
          name=QString::number(i)+".obj";
        objLoaders_toss2[i-1]->loadModel("C:/homework3/toss/"+name);
        objLoaders_toss2[i-1]->fileName=name;

        objLoader2=objLoaders_toss2[i-1];
        geometries = new GeometryEngine(objLoader2);
        Sleep(1000);
    }
*/
    geometries = new GeometryEngine();

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void openglWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void openglWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void openglWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.1, zFar = 100.0, fov = 60.0;

    // Reset projection
    ProjMat.setToIdentity();

    // Set perspective projection
    ProjMat.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void openglWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //texture->bind();

    ViewMat.lookAt(QVector3D(0, 0, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    //ProjMat.perspective(45, width()/ height(), 3, 7);
    //qDebug()<<width() << " "<<height();

//! [6]

    QMatrix4x4 ModelMat;

    //ModelMat.translate(0,0,-5);

   //ModelMat.translate(geometries->transtlateAvg);
   ModelMat.translate(0,0,-5);
    //ModelMat.translate(0,0,-5);
    ModelMat.rotate(rotation);
    //ModelMat.scale(geometries->scaleAll,geometries->scaleAll,geometries->scaleAll);
    ModelMat.scale( 0.1,0.1,0.1);

    program.setUniformValue("mvp_matrix", ProjMat*ModelMat);

    program.setUniformValue("uProjMat", ProjMat);
    program.setUniformValue("uModelMat", ModelMat);
    program.setUniformValue("uFrameNum",frameNum);


//! [6]

    // Use texture unit 0 which contains cube.png
    //  program.setUniformValue("texture", 0);

    // Draw cube geometry
/*
    for(int i=0;i<26;i++)
    {
        geometries->objLoader = geometries->objLoaders_toss[i];
        qDebug()<<geometries->objLoader->fileName;
        geometries->drawObjArray(&program);
        Sleep(500);
    }
*/
    /*

    for(int i=0;i<26;i++)
    {
        geometries->toss_index=i;
        geometries->drawObjGeometry(&program);

    }
    */

     geometries->drawObjGeometry(&program);
     progress_bar.setValue(geometries->toss_index);
}

/*
void openglWidget::on_pushButton_clicked()
{
    geometries->normalFlag=1;
}


void openglWidget::on_pushButton_2_clicked()
{
    geometries->normalFlag=0;
}
*/


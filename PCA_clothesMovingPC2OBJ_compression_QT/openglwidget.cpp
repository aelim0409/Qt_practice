#include "openglwidget.h"
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include <QVector3D>


float frameNum=23;
int flag_t=1;
int flag_index=0;


openglWidget::openglWidget(QWidget *par)
{
    ui.setupUi(this);
    /*
   progress_bar.setMaximum(26);
   progress_bar.setMinimum(1);
   progress_bar.setOrientation(Qt::Horizontal);
   progress_bar.setGeometry(10,30,700,30);
   progress_bar.setVisible(true);
   */



    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
     connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(ButtonClicked_2()));
     connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(ButtonClicked_3()));
     connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(ButtonClicked_4()));
      connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(ButtonClicked_5()));
      connect(ui.playButton, SIGNAL(clicked()), this, SLOT(ButtonClicked_play()));


    QWidget widget;
    widget.setVisible(true);

    ui.PC_Slider->setMaximum(7);
    ui.PC_Slider->setMinimum(-3);
    ui.PC_Slider->setSingleStep(1);
    ui.playSlider->setMinimum(0);
    ui.playSlider->setMaximum(218);
    ui.label->setVisible(true);
    ui.label->setText("0");


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
//!
//!
//!
//!

void openglWidget::ButtonClicked_play()
{

    if( geometries->playFlag)
    {
         geometries->playFlag=false;
         qDebug()<<"STOP!";
    }
    else
    {
        geometries->playFlag=true;
        qDebug()<<"PLAY!";
    }
   // geometries->toss_index+=flag_index;
    /*
    if(geometries->toss_index>=geometries->binReader->st_info.num_samples/2)
        flag_index=-1;
    else if(geometries->toss_index<=0)
        flag_index=1;
*/
    ui.label->setText(QString::number(geometries->toss_index));


}

void openglWidget::ButtonClicked()
{
    qDebug()<<"clicked!";
    geometries->PCA.pcaPCClick=true;
    geometries->PCA.pcaPC(0,ui.PC_Slider->value());
}
void openglWidget::ButtonClicked_2()
{
    qDebug()<<"clicked2!";
    geometries->PCA.pcaPCClick=true;
    geometries->PCA.pcaPC(1,ui.PC_Slider->value());
}
void openglWidget::ButtonClicked_3()
{
    qDebug()<<"clicked3!";
    geometries->PCA.pcaPCClick=true;
    geometries->PCA.pcaPC(2,ui.PC_Slider->value());
}
void openglWidget::ButtonClicked_4()
{
    qDebug()<<"clicked4!";
    geometries->PCA.pcaPCClick=true;
    geometries->PCA.pcaPC(3,ui.PC_Slider->value());
}
void openglWidget::ButtonClicked_5()
{
    qDebug()<<"clicked5!";
    geometries->PCA.pcaPCClick=true;
    geometries->PCA.pcaPC(4,ui.PC_Slider->value());
}
void openglWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
    qDebug()<<"rotate!";
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

void openglWidget::keyPressEvent(QKeyEvent *e)
{
        if(e->key()==Qt::Key_A)
        {
            //if(geometries->toss_index>=26)
                flag_t=-1;

            if(geometries->toss_index+flag_t<0)
                 geometries->toss_index=0;
            else
                geometries->toss_index+=flag_t;

            qDebug()<< "A! "<< geometries->toss_index;


        }

        if(e->key()==Qt::Key_D)
        {
            //geometries->normalFlag=1;

          // if(geometries->toss_index<=0)
                flag_t=1;

            if(geometries->toss_index+flag_t>25)
                 geometries->toss_index=25;
            else
                geometries->toss_index+=flag_t;

            qDebug()<< "D! "<< geometries->toss_index;

        }



}
//! [0]

//! [1]
void openglWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
   // angularSpeed *= 0.99;
    mytime+=1;
    /*
    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
*/

    // Request an update
    update();
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

    geometries = new GeometryEngine();

    //geometries->initObjPCA();
    // Use QBasicTimer because its faster than QTimer
    timer.start(0.003, this);
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
    float aspect = qreal(w) / qreal(h ? h : 1);


    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //qreal zNear = -10, zFar = 100, fov = 45.0;

    float zNear =  QVector3D(-47.8453, -492.15, -301.308).length()*1.2/100
            , zFar =  QVector3D(-47.8453, -492.15, -301.308).length()*1.2*2, fov = 45.0;
    qDebug()<<"zNear zFar"<<zNear<<zFar;
    // qDebug()<<geometries->transtlateAvg;
    // Reset projection
    ProjMat.setToIdentity();

    // Set perspective projection
   // ProjMat.perspective(fov, aspect, zNear, zFar);
     ProjMat.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void openglWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //texture->bind();




//! [6]

    QMatrix4x4 ModelMat;

    //ModelMat.translate(0,0,-5);

   ModelMat.translate(geometries->transtlateAvg);
   qDebug()<<"oo"<<geometries->transtlateAvg;
   //ModelMat.translate(0,0,-5);
    //ModelMat.translate(0,0,-5);
    //ModelMat.rotate(0,mytime,0);
   //ModelMat.rotate(rotation);
   //ModelMat.scale(geometries->scaleAll,geometries->scaleAll,geometries->scaleAll);

    ModelMat.scale( geometries->scaleAll,geometries->scaleAll,geometries->scaleAll);

    ViewMat.lookAt(QVector3D(0, 0, 2), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    program.setUniformValue("mvp_matrix", ProjMat*ViewMat*ModelMat);

    program.setUniformValue("uProjMat", ProjMat);
    program.setUniformValue("uModelMat",ViewMat* ModelMat);
    program.setUniformValue("uFrameNum",frameNum);


     geometries->drawObjGeometry(&program);
     ui.playSlider->setValue(geometries->toss_index);
   //progress_bar.setValue(geometries->toss_index);
}




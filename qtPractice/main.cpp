#include "mainwindow.h"

#include <QApplication>
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
#define _CRT_SECURE_NO_WARNINGS

#include <qopenglextrafunctions.h>
#include <mat.h>
#include "mytorus.h"
#include <string.h>

using namespace std;


MyTorus torus;
QOpenGLShaderProgram program;
QOpenGLShaderProgram prog_phong;

GLuint uMat;
GLuint uColor;
mat4 g_Mat = mat4(1.0f);

int winWidth = 500;
int winHeight = 500;

bool is_phong = true;
bool is_rotation = true;
int rotationaxis = 1;
float mytime = 0;
int filenum = 0;

float mSpec = 0.7;
float Shininess = 100;


mat4 myLookAt(vec3 eye, vec3 at, vec3 up)
{
    // Implement your own look-at function
    mat4 V(1.0f);
    vec3 n = at - eye;
    n /= length(n);

    float a = dot(up, n);
    vec3 v = up - a * n;
    v /= length(v);

    vec3 w = cross(n, v);

    mat4 Rw(1.0f);

    Rw[0][0] = w.x;   Rw[0][1] = v.x; Rw[0][2] = -n.x;
    Rw[1][0] = w.y;   Rw[1][1] = v.y; Rw[1][2] = -n.y;
    Rw[2][0] = w.z;   Rw[2][1] = v.z; Rw[2][2] = -n.z;

    mat4 Rc(1.0f);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Rc[i][j] = Rw[j][i];

    mat4 Tc = Translate(-eye.x, -eye.y, -eye.z);

    V = Rc * Tc;

    return V;
}

mat4 myPerspective(float fovy, float aspectRatio, float zNear, float zFar)
{
    mat4 P(1.0f);

    float rad = fovy * 3.141592 / 180.0;

    float sz = 1 / zFar;
    float h = zFar * tan(rad / 2);

    float sy = 1 / h;
    float w = h * aspectRatio;
    float sx = 1 / w;

    mat4 S = Scale(sx, sy, sz);
    mat4 M(1.0f);

    float c = -zNear / zFar;
    M[2][2] = 1 / (c + 1);
    M[2][3] = -c / (c + 1);
    M[3][2] = -1;
    M[3][3] = 0;

    P = M * S;

    return P;
}

void myInit()
{
    //sphere.Init(20, 20, vec4(1, 0, 0, 0));
    torus.Init();
   program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
   program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");

    prog_phong.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_phong.glsl");
     prog_phong.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader_phong.glsl");
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    mat4 ModelMat = RotateY(mytime);

    mat4 ViewMat = myLookAt(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));

    float aspect = winWidth / (float)winHeight;
    float h = 1;

    mat4 ProjMat = myPerspective(60, aspect, 0.1, 100);

    g_Mat = ProjMat * ViewMat;

    prog_phong.bind();


    vec4 spc = vec4(mSpec, mSpec, mSpec, 1);

    prog_phong.setUniformValue("uProjMat", ProjMat);
    prog_phong.setUniformValue("uModelMat", ViewMat * ModelMat);
    prog_phong.setUniformValue("uSpc", spc);
    prog_phong.setUniformValue("uShininess", Shininess);
    prog_phong.setUniformValue("uTime", mytime);
   // glUniformMatrix4fv(uProjMat, 1, GL_TRUE, ProjMat);
   // glUniformMatrix4fv(uModelMat, 1, GL_TRUE, ViewMat * ModelMat);
  //  glUniform4f(uSpc, spc[0], spc[1], spc[2], spc[3]);
//    glUniform1f(uShininess, Shininess);
//    glUniform1f(uTime, mytime);

    torus.Draw(&prog_phong);

    glutSwapBuffers();
}

void idle()
{
    if (is_rotation == true) {
        mytime += 1;
        Sleep(33);               // for vSync
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);

    glutCreateWindow("hw");

    glewExperimental = true;
    glewInit();

    myInit();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

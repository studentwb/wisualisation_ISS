#include "glwidget.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <QtOpenGL>
#include <QtGui>
#include <QtCore/QDebug>
#include <Qt3DExtras/QSphereMesh>
#include <QGLViewer/qglviewer.h>
#include <QtGui/QImage>
#include <GLFW/glfw3.h>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QTextureImage>
#include <Qt3DExtras/QCuboidMesh>
#include <SOIL/SOIL.h>
#include <iostream>
#include <QWindow>
#include <QMainWindow>
#include <QOpenGLWindow>
#include <cmath>
#include <QGLViewer/manipulatedFrame.h>
#include <QMouseEvent>
using namespace qglviewer;
using namespace std;
inline
double Deg2Rad(double Ang_deg)
  { return Ang_deg*M_PI/180; }

#define SLIDER2RAD(x) static_cast<float>(sin(M_PI*2*ScnParams.Get##x##_Light_deg()/180))
#define ANG_STEP_deg 10
GLWidget::GLWidget(QWidget *parent) : QGLViewer(parent)
 {
angle=0.0;
}

void GLWidget::init()
{
GLfloat light_position[]={3.0, 3.0, 3.0, 0.0};
restoreFromFile();
glEnable(GL_DEPTH_TEST);
 glEnable(GL_LIGHT0);
glEnable(GL_LIGHTING);

}


void GLWidget::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);


     glColor3f(1, 0.5, 0);
    // glViewport(0, 0, 470, 470);
//    gluLookAt(0,0.8,-1,0,0,0,0,2,0);
    drawSphere(0.5, 1000, 1000);
     glClearColor(0,0,0.5,1);
    rotateISS();

   }

/*
void GLWidget::resizeGL(int w, int h){

}*/
void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
   // update();
}
void GLWidget::drawISS(double Size){

    glScalef( Size, Size, Size );

    float   x_new_z_new;
    float   y_new_z_new;


    float   radius_new;
    float   sn, cs;


      radius_new = 1;
      sn = 0;  cs = 1;

      glBegin(GL_QUAD_STRIP);
      glColor3f(   0.0,  0.0,  1.0 );

      for (double Azim_deg = 0; Azim_deg <= 360; Azim_deg += ANG_STEP_deg) {
       sn = sin(Deg2Rad(Azim_deg));  cs = cos(Deg2Rad(Azim_deg));
       x_new_z_new = radius_new*cs;
       y_new_z_new = radius_new*sn;

       glNormal3f( x_new_z_new, y_new_z_new,  0);  glVertex3f( x_new_z_new, y_new_z_new,  0 );
       glNormal3f(x_new_z_new, y_new_z_new,  0);   glVertex3f( x_new_z_new, y_new_z_new,  5 );
      }
glEnd();
      glBegin( GL_QUADS ); // Rysujemy kwadraty
       glColor3f( 1.0, 1.0,  1.0 );
       glVertex3f( 0.0f, - 5.0f, 5.0f ); // górny lewy
       glVertex3f( 0.0f , 5.0f, 5.0f); // górny prawy git
       glVertex3f( 0.0f, 5.0f, -0.1f); // dolny prawy
       glVertex3f( 0.0f , - 5.0f, -0.1f); // dolny lewy



      glEnd();

}

void GLWidget::rotateISS(){
    update();
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0,0,0.7);
    drawISS(0.05);
    glPopMatrix();
    angle +=1.0f;
    if(angle==360){        angle=0;}
}

void GLWidget::drawSphere(double r, int lats, int longs)
{
    int i;
    int j;
      for(i = 0; i <= lats; i++) {
          double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
          double z0  = sin(lat0);
          double zr0 =  cos(lat0);

          double lat1 = PI * (-0.5 + (double) i / lats);
          double z1 = sin(lat1);
          double zr1 = cos(lat1);

          glBegin(GL_QUAD_STRIP);
          for(j = 0; j <= longs; j++) {
              double lng = 2 * PI * (double) (j - 1) / longs;
              double x = cos(lng);
              double y =sin(lng);

              glNormal3f(x * zr0, y * zr0, z0);
              glVertex3f(r * x * zr0, r * y * zr0, r * z0);
              glNormal3f(x * zr1, y * zr1, z1);
              glVertex3f(r * x * zr1, r * y * zr1, r * z1);
          }
          glEnd();
     }

    /*

    // Sphere shape data
      Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
      sphereMesh->setRings(32);
      sphereMesh->setSlices(32);
      sphereMesh->setRadius(4);

      // Sphere mesh transform
      Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();
      sphereTransform->setScale(1.0f);
      sphereTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
      sphereTransform->setRotation(QQuaternion(1.0f, 0.0f, 0.0f, 0.0f));

      Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
      sphereMaterial->setDiffuse(QColor(QRgb(0xA69929)));

      // Sphere
      m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
      m_sphereEntity->addComponent(sphereMesh);*/
}


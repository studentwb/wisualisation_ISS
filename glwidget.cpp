#include "glwidget.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
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
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
 {

}


void GLWidget::initializeGL()
{
 glClearColor(0,0,1,1);
glEnable(GL_DEPTH_TEST);
GLfloat light_position[]={-1.0, 1.0, -1.0, 0.0};
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 glEnable(GL_LIGHT0);
glEnable(GL_LIGHTING);
 glEnable(GL_COLOR_MATERIAL);
// initializeOpenGLFunctions();


}


void GLWidget::paintGL(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
//QSphereMesh; //pojdz w tym kierunku

    glViewport(0, 0, 470, 470);
   drawSphere(0.3, 1000, 1000);
   //glViewport(a2, a3, -100, 470, 470);
  // glViewport(0, 0, 470, 470);
//drawISS();

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
void GLWidget::drawISS(){



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


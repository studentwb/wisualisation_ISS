#include "glwidget.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <QtOpenGL>
#include <QtGui>
#include <QtCore/QDebug>
#include <Qt3DExtras/QSphereMesh>
#include <QGLViewer/qglviewer.h>
#include <QtGui/QImage>
//#include <GLFW/glfw3.h>
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
#include <unistd.h>
#include <QDebug>
float a1, a2, a3, a4;
using namespace qglviewer;
using namespace std;
inline double Deg2Rad(double Ang_deg)
  { return Ang_deg*M_PI/180; }
static GLuint Texture4Bg;
static GLuint Texture4Earth;
#define SLIDER2RAD(x) static_cast<float>(sin(M_PI*2*ScnParams.Get##x##_Light_deg()/180))
#define ANG_STEP_deg 10

GLWidget::GLWidget(QWidget *parent) : QGLViewer(parent)
 {
angle=0.0;
}

void GLWidget::init()
{
    restoreStateFromFile();
    GLfloat Light1_Position[] = { 1.0, 1.0, 1.0, 0.0 };
     glLightfv(GL_LIGHT0, GL_POSITION, Light1_Position);

     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_DEPTH_TEST);
Texture4Bg = SOIL_load_OGL_texture
(
    "/home/baron/Pobrane/WDSstacja/source/space_dust.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
  );


glEnable(GL_TEXTURE_2D);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glGenTextures(1, &Texture4Earth);
glBindTexture(GL_TEXTURE_2D, Texture4Earth);

glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
         GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_NEAREST);


int width, height;
unsigned char* image =
     SOIL_load_image("/home/baron/Pobrane/WDSstacja/source/earth.jpg", &width, &height, 0, SOIL_LOAD_RGB);
qDebug()<<"zdjedzie " <<image;
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
}


void GLWidget::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glEnable(GL_TEXTURE_2D);
       glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
       glBindTexture(GL_TEXTURE_2D, Texture4Bg);

       glMatrixMode(GL_MODELVIEW);
       glPushMatrix();

       glLoadIdentity();
       glDepthMask(GL_FALSE);

       glMatrixMode(GL_PROJECTION);
       glPushMatrix();

       glLoadIdentity();
       glOrtho(0,1,1,0,-1,1);

       glBegin(GL_QUADS);  // Tworzenie kwadratu, na którym będzie
        glTexCoord2f(0,0); // rozpięta tekstura tła.
        glVertex2f(0,0);

        glTexCoord2f(1,0);
        glVertex2f(1,0);

        glTexCoord2f(1,1);
        glVertex2f(1,1);

        glTexCoord2f(0,1);
        glVertex2f(0,1);
      glEnd();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
      glDepthMask(GL_TRUE);

      glDisable(GL_TEXTURE_2D);

     glColor3f(0.0, 0.0, 0);


glDepthMask(GL_TRUE);


glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glScalef( 0.5, 0.5, 0.5 );
glColor3f(   1.0,  0.0,  0.0 );
drawSphere(0.6371, 1000, 1000); //R Earth=6371km
glColor3f(   1.0,  0.0,  0.0 );
   //drawPath();
   rotateISS();

   }


void GLWidget::drawPath(){

    update();
   // glPushMatrix();
    glRotatef(angle, 0.0f+a1/1000.0, 0.0f+a2/1000.0, 0.0f);
     glTranslatef(0, 0.6371+(a3/1000.0),0.0);
     glColor3f(   1.0,  0.0,  0.0 );
      drawSphere(0.01, 1000, 1000);
    glPopMatrix();
    angle +=a4/(105160);
    if(angle==360){        angle=0;}

}

void GLWidget::rotateISS(){

    update();
    glPushMatrix();
    glRotatef(angle, 0.0f+a1/1000.0, 0.0f+a2/1000.0, 0.0f);
     glTranslatef(0, 0.6371+(a3/1000.0),0.0);
      drawISS(0.01);
    glPopMatrix();
    angle +=a4/(105160);
    if(angle==360){        angle=1;}
}

void GLWidget::drawSphere(double r, int lats, int longs)
{

    int i;
    int j;

    glBindTexture(GL_TEXTURE_2D, Texture4Earth);

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
       glVertex3f( 0.0f, - 5.0f, 5.0f ); // górny lewy
       glVertex3f( 0.0f , 5.0f, 5.0f); // górny prawy git
       glVertex3f( 0.0f, 5.0f, -0.1f); // dolny prawy
       glVertex3f( 0.0f , - 5.0f, -0.1f); // dolny lewy
      glEnd();

}

void GLWidget::getData_1(float value_longitude){
    qDebug() <<value_longitude;
    a1=value_longitude;
}
void GLWidget::getData_2(float value_latitude){
qDebug() <<value_latitude;
a2=value_latitude;
}
void GLWidget::getData_3(float value_altitude)
{
    qDebug() <<value_altitude;
    a3=value_altitude;
}
void GLWidget::getData_4(float value_velocity)
{
    qDebug() <<value_velocity;
    a4=value_velocity;
}


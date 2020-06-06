#include "glwidget.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include "SceneParams.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <QtOpenGL>
#include <QtGui>
#include <QtCore/QDebug>
#include <QGLViewer/qglviewer.h>
#include <QtGui/QImage>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
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
#include <QList>
float a1, a2, a3, a4;
using namespace qglviewer;
using namespace std;
QList<float> vectorA={0.0, 0.1};
QList<float> vectorB={0.0, 0.1};
QList<float> vectorC={0.0, 0.1};
int i=0;
inline
double Deg2Rad(double Ang_deg)
  { return Ang_deg*M_PI/180; }
static GLuint Texture4Bg;
static GLuint Texture4Sphere;
#define SLIDER2RAD(x) static_cast<float>(sin(M_PI*2*ScnParams.Get##x##_Light_deg()/180))
#define ANG_STEP_deg 10

GLWidget::GLWidget(QWidget *parent) : QGLViewer(parent)
 {
angle=0.0;
}

void GLWidget::init()
{
    restoreStateFromFile();

      GLfloat Light1_Position[] = { 3.0, 3.0, 3.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_POSITION, Light1_Position);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_DEPTH_TEST);


      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glGenTextures(1, &Texture4Sphere);
      glBindTexture(GL_TEXTURE_2D, Texture4Sphere);

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

       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image);

       /* Inny sposob powiazania z tekstura */
       Texture4Bg = SOIL_load_OGL_texture(
            "/home/baron/Pobrane/WDSstacja/source/space_dust.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
               );

}
void CreateBackground()
{
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
}

void GLWidget::draw(){

GLfloat Light1_Position[]={1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, Light1_Position);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    CreateBackground();

    glDepthMask(GL_TRUE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // TMP
    glBindTexture(GL_TEXTURE_2D, Texture4Sphere);


    drawSphere(0.6371);
    glFlush();
    glDisable(GL_TEXTURE_2D);
    drawPath();
    rotateISS();
  //  drawAxis(1.1);
   }


void GLWidget::drawPath(){
        dataPath();
        glPointSize(3);
        glBegin(GL_LINE_STRIP);
        glPushMatrix();
        /// SPrawdza czy tablice nie są puste \n
        /// jeżeli są puste to nie generują się koljen punkty, które odpowiadają za ścieżkę
        if(vectorA.size()!=0 || vectorB.size()!=0 || vectorC.size()!=0){
        for(i=(vectorA.size()/10); i<vectorA.size(); ++i){
            if(i<=1){
                 glVertex3f(vectorA[0], vectorB[0], vectorC[0]);
                 glVertex3f(vectorA[1], vectorB[1], vectorC[1]);}
            else{
                glVertex3f(vectorA[i-1], vectorB[i-1], vectorC[i-1]);
                glVertex3f(vectorA[i], vectorB[i], vectorC[i]);}
                 qDebug()<<vectorA.size()<< vectorB[i]<< vectorC[i];
glEnd();
glBegin(GL_POINTS);
                 glVertex3f(vectorA[i], vectorB[i], vectorC[i]);
        }
        }
        glEnd();
           glPopMatrix();
}
void GLWidget::dataPath(){

    GLfloat a11, a22, a33;
    a11=1.2*sin(Deg2Rad(a1));
    a22=1.2*sin(Deg2Rad(a2));
    a33=1.2*cos(Deg2Rad(a1));
    vectorA.push_back(a11);
    vectorB.push_back(a22);
    vectorC.push_back(a33);
   // qDebug()<<a1<<a2<<"|"<<a11<<a22<<a33<<"|"<<Deg2Rad(a1)<<Deg2Rad(a2);

}

void GLWidget::rotateISS(){
     GLfloat a111, a222, a333;
     a111=1.2*sin(Deg2Rad(a1));
     a222=1.2*sin(Deg2Rad(a2));
     a333=1.2*cos(Deg2Rad(a1));
     update();
     glPushMatrix();

     glTranslatef( a111, a222, a333);
     drawISS(0.01);
     glPopMatrix();
     angle +=a4/(10516000);
     if(angle==360){        angle=1;}

}

void GLWidget::drawSphere(double Size)
{

    glScalef( Size, Size, Size );

     float   x_new_z_prev, y_new_z_prev;
     float   x_new_z_new,  y_new_z_new;
     float   z_prev = -1, z_new;
     float   radius_prev = 0, radius_new;
     float   sn, cs;

     glBindTexture(GL_TEXTURE_2D, Texture4Sphere);

     double  s_new;
     double  t_prev = 0, t_new;

     for (double Elev_deg = -90+ANG_STEP_deg; Elev_deg <= 90; Elev_deg += ANG_STEP_deg) {
       z_new = sin(Deg2Rad(Elev_deg));
       radius_new = cos(Deg2Rad(Elev_deg));

       t_new =  (90+Elev_deg)/180;
       sn = 0;  cs = 1;


       glBegin(GL_QUAD_STRIP);
       glColor3f(   1.0,  1.0,  1.0 );

       for (double Azim_deg = 0; Azim_deg <= 360; Azim_deg += ANG_STEP_deg) {
        s_new = Azim_deg/360;
        sn = sin(Deg2Rad(Azim_deg));  cs = cos(Deg2Rad(Azim_deg));
        x_new_z_new = radius_new*cs;
        y_new_z_new = radius_new*sn;
        x_new_z_prev = radius_prev*cs;
        y_new_z_prev = radius_prev*sn;

        glTexCoord2f(s_new,t_prev);
        glNormal3f( x_new_z_prev, y_new_z_prev,  z_prev);  glVertex3f( x_new_z_prev, y_new_z_prev,  z_prev );
        glTexCoord2f(s_new,t_new);
        glNormal3f(x_new_z_new, y_new_z_new,  z_new);      glVertex3f( x_new_z_new, y_new_z_new,  z_new );
       }

       glEnd();

      z_prev = z_new;
      radius_prev = radius_new;
      t_prev = t_new;
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
      glColor3f(   1.0,  0.0,  0.0 );

      for (double Azim_deg = 0; Azim_deg <= 360; Azim_deg += ANG_STEP_deg) {
       sn = sin(Deg2Rad(Azim_deg));  cs = cos(Deg2Rad(Azim_deg));
       x_new_z_new = radius_new*cs;
       y_new_z_new = radius_new*sn;

       glNormal3f( x_new_z_new, y_new_z_new,  0);  glVertex3f( x_new_z_new, y_new_z_new,  0 );
       glNormal3f(x_new_z_new, y_new_z_new,  0);   glVertex3f( x_new_z_new, y_new_z_new,  5 );
      }
glEnd();
      glBegin( GL_QUADS ); // Rysujemy kwadraty
      glColor3f(   1.0,  0.0,  0.0 );

       glVertex3f( 0.0f, - 5.0f, 5.0f ); // górny lewy
       glVertex3f( 0.0f , 5.0f, 5.0f); // górny prawy git
       glVertex3f( 0.0f, 5.0f, -0.1f); // dolny prawy
       glVertex3f( 0.0f , - 5.0f, -0.1f); // dolny lewy
      glEnd();

}

void GLWidget::getData_1(float value_longitude){
  //  qDebug() <<value_longitude;
    a1=value_longitude;

}
void GLWidget::getData_2(float value_latitude){
//qDebug() <<value_latitude;
a2=value_latitude;
}
void GLWidget::getData_3(float value_altitude)
{
  //  qDebug() <<value_altitude;
    a3=value_altitude;
}
void GLWidget::getData_4(float value_velocity)
{
  //  qDebug() <<value_velocity;
    a4=value_velocity;
}


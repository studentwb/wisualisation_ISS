#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QGLViewer/qglviewer.h>
#include <Qt3DExtras/QSphereMesh>
#include <QtCore/QObject>
#include <QOpenGLFunctions>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QGLWidget>
#include <GL/glu.h>
class GLWidget : public QGLViewer
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    float angle;

    void drawSphere(double r, int lats, int longs);
    void rotateISS();
    void drawISS(double Size);
    void rotateBy(int xAngle, int yAngle, int zAngle);
  //  void resizeGL(int w, int h);
private:
    void makeObject();
   int xRot;
    int yRot;
    int zRot;
protected:
     void init();
     void draw();
};

#endif // GLWIDGET_H

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

#include <QGLViewer/qglviewer.h>
#include <Qt3DExtras/QSphereMesh>
#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>



class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void initializeGL();
    void drawSphere(double r, int lats, int longs);
    void paintGL();
    void drawISS();
    void rotateBy(int xAngle, int yAngle, int zAngle);
  //  void resizeGL(int w, int h);
private:
    void makeObject();
   int xRot;
    int yRot;
    int zRot;


signals:

};

#endif // GLWIDGET_H

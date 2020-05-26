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

    void drawSphere(double Size);
    void rotateISS();
    void drawISS(double Size);
    void drawPath();
    void dataPath();
private:
    void makeObject();
protected:
     void init();
     void draw();
private slots:
     void getData_1(float value_longitude);
     void getData_2(float value_latitude);
     void getData_3(float value_altitude);
     void getData_4(float value_velocity);
};




#endif // GLWIDGET_H

#include "mainwindow.h"
#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <GL/glu.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <QSurfaceFormat>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <QApplication>
/**************************************************************************************************************
 **************************************************************************************************************/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSurfaceFormat format;

    MainWindow w;
     w.setWindowTitle("Wizualizacja ISS");
     w.resize(1000, 550);
    w.show();
    return a.exec();
}

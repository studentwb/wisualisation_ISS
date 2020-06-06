#ifndef GLWIDGET_H
#define GLWIDGET_H
/*!
 *
 * \brief Klasa glwidget
 * Zawiera definicję klasy glwidget, ktora odpowiada
 * za generowanie obiektów 3d, nakladanie tekstur oraz przetwarzania danych potrzebnych do generowania punktow
 *
 */
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
    /*!
        * \brief Konstruktor
        * \param parent
        */
    explicit GLWidget(QWidget *parent = nullptr);
    float angle;
    /*!
        * \brief rysuje sfere, ktora odpowaida za tworzenie modelu planety
        * \param Size - rozmiar sfery
        */
    void drawSphere(double Size);
    /*!
        * \brief Obraca modelem miedzynarodowej stacji kosmicznej
        *
        */
    void rotateISS();
    /*!
        * \brief Tworzy model 3d Miedzynordowej stacji komsicznej
        * \param Size- rozmiar stacji
        */
    void drawISS(double Size);
    /*!
        * \brief Odpowiada za rysowanie sciezki, ktora przebyla miedzynarodowa stacja kosmiczna
        *
        */
    void drawPath();
    /*!
        * \brief Odpowiada za przetwarzanie danych miedzynarodowa stacja kosmiczna
        * \return Punty w przestrenii kartezjanskiej
        */
    void dataPath();
private:
    void makeObject();
protected:
     void init();
     void draw();
private slots:
     /*!
         * \brief Odpowiada za pobieranie danych od klasu mainwindow
         * \param value_longitude - dlugosc geograficzna w stopniach
         */
     void getData_1(float value_longitude);
     /*!
         * \brief Odpowiada za pobieranie danych od klasu mainwindow
         * \param value_latitude - szerokosc geograficzna w stopniach
         */
     void getData_2(float value_latitude);
     /*!
         * \brief Odpowiada za pobieranie danych od klasu mainwindow
         * \param value_altitude - odleglosc od skorupy ziemskiej w kilometrach
         */
     void getData_3(float value_altitude);
     /*!
         * \brief Odpowiada za pobieranie danych od klasu mainwindow
         * \param value_velocity - predkosc w kilometrach na godzine
         */
     void getData_4(float value_velocity);
};




#endif // GLWIDGET_H

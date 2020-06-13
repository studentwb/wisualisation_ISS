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
        * \brief rysuje sfere, która odpowaida za tworzenie modelu planety
        * \param[in] Size - rozmiar sfery
        */
    void drawSphere(double Size);
    /*!
        * \brief Obraca modelem międzynarodowej stacji kosmicznej
        *
        */
    void rotateISS();
    /*!
        * \brief Tworzy model 3d Międzynordowej stacji komsicznej
        * \param[in] Size- rozmiar stacji
        */
    void drawISS(double Size);
    /*!
        * \brief Odpowiada za rysowanie ścieżki, która przebyła miedzynarodowa stacja kosmiczna
        *
        */
    void drawPath();
    /*!
        * \brief Odpowiada za przetwarzanie danych miedzynarodowej stacji kosmicznej
        * Funkcja przekształca szerkość i długość geograficzna na punkty w przestrenii kartezjańskiej
        */
    void dataPath();
private:
    void makeObject();
protected:
     void init();
     void draw();
private slots:
     /*!
         * \brief Odpowiada za pobieranie danych z klasy MainWindow
         * \param[in] value_longitude - długość geograficzna podana w stopniach
         */
     void getData_1(float value_longitude);
     /*!
         * \brief Odpowiada za pobieranie danych z klasy MainWindow
         * \param[in] value_latitude - szerokość geograficzna podana w stopniach
         */
     void getData_2(float value_latitude);
     /*!
         * \brief Odpowiada za pobieranie danych z klasy MainWindow
         * \param[in] value_altitude - odleglość od skorupy ziemskiej podana w kilometrach
         */
     void getData_3(float value_altitude);
     /*!
         * \brief Odpowiada za pobieranie danych z klasy MainWindow
         * \param[in] value_velocity - szybkość podana w kilometrach na godzine
         */
     void getData_4(float value_velocity);
};




#endif // GLWIDGET_H

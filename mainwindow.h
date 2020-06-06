#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*!
 *
 * \brief Klasa mainwindow
 * Zawiera definicję klasy MainWindow, ktora odpowiada
 * za pobieranie danych z API oraz obsługę sygnalow i slotow.
 *
 */
#include <glwidget.h>
#include <QMainWindow>
#include <QJsonDocument>
#include <QLCDNumber>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \brief Klasa MainWindow
 * Klasa zawiera w sobie dane o aktualnej pogodzie, oraz funkcję przetwarzająca
 * odpowiedź WeatherAPI.
 */


/*!
 * \brief Klasa MainWindow
 * Klasa dziedzicząca QMainWindow stanowiąca główne okno aplikacji.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief on_pushButton_clicked
     * odpowiada za odswiezanie aplikacji w przypadku bledow
     *
     */
    void on_pushButton_clicked();
    /*!
     * \brief on_results
     * \param reply- sprawdza czy polaczenie jest aktywne i nie wystapppil blad
     * Pobiera dane z API, dzieki czemu aplikacja moze dzialac i przetwarzac dane
     */
    void on_results(QNetworkReply *reply);


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *mManager;
    QNetworkRequest request;
    QTimer *timer;
signals:
    /*!
       * \brief sendData_1
       * \param a1- przeysla wartosc szerokosci geograficznej [kąt]
       */
    void sendData_1(float a1); //przesyly danych
    /*!
       * \brief sendData_2
       * \param a1- przeysla wartosc dlugosci geograficznej [kąt]
       */
    void sendData_2(float a2);
    /*!
       * \brief sendData_3
       * \param a1- przeysla wartosc wysokosci ISS [km]
       */
    void sendData_3(float a3);
    /*!
       * \brief sendData_4
       * \param a1- przeysla wartosc predkosci ISS [km/h]
       */
    void sendData_4(float a4);
};
#endif // MAINWINDOW_H

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
 * Klasa odpowiada za pobieranie danych ze strony internetowej oraz ich przetwarzanie
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
     * odpowiada za odswieżanie aplikacji w przypadku błędów
     *
     */
    void on_pushButton_clicked();
    /*!
     * \brief on_results
     * \param[in] reply- sprawdza czy połączenie jest aktywne i czy nie wystąpił błąd
     * Pobiera dane z API, dzięki czemu aplikacja może działać i przetwarzać dane
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
       * \param[in] current_longitude- przesyła wartość szerokosci geograficznej [kąt]
       */
    void sendData_1(float current_longitude);
    /*!
       * \brief sendData_2
       * \param[in] current_latitude- przesyła wartość długosci geograficznej [kąt]
       */
    void sendData_2(float current_latitude);
    /*!
       * \brief sendData_3
       * \param[in] current_altitude- przesyła wartość wysokosści ISS [km]
       */
    void sendData_3(float current_altitude);
    /*!
       * \brief sendData_4
       * \param[in] current_velocity- przesyła wartość szybkości ISS [km/h]
       */
    void sendData_4(float current_velocity);
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*!
 * \file
 * \brief
 *
 * Plik zawiera definicję klasy MainWindow, ktora odpowiada
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \file
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
    void sendData_1(float a1); //przesyly danych
    void sendData_2(float a2);
    void sendData_3(float a3);
    void sendData_4(float a4);
};
#endif // MAINWINDOW_H

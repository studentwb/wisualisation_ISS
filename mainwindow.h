#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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

    void on_pushButton_clicked();
    void on_results(QNetworkReply *reply);


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *mManager;
    QNetworkRequest request;
    QTimer *timer;
signals:
    void test(float a1); //przesyly danych
    void sendData_2(float a2);
    void sendData_3(float a3);
    void sendData_4(float a4);
};
#endif // MAINWINDOW_H

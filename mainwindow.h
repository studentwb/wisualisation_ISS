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
    QGLWidget *a1;
    QGLWidget *a2;
    QGLWidget *a3;
    QGLWidget *a4;

};
#endif // MAINWINDOW_H

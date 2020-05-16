#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QJsonDocument>
#include <QLCDNumber>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtOpenGL>
#include <QtGui>
#include <iostream>
#include <QTimer>
#include <QString>
#include <QDebug>
#include <unistd.h>
#include <QMessageBox>
#include <QTextStream>
#define PI 3.1415
double a1;
int a2;
int a3;
double a4;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer= new QTimer(this);
    mManager = new QNetworkAccessManager(this);
    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(on_results(QNetworkReply*)));
    mManager->get(QNetworkRequest(QUrl("https://api.wheretheiss.at/v1/satellites/25544")));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));
    timer->start(1000);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete mManager;

}


void MainWindow::on_pushButton_clicked()
{    
    request.setUrl(QUrl(QString("https://api.wheretheiss.at/v1/satellites/25544")));
    mManager->get(request);   

}

void MainWindow::on_results(QNetworkReply *reply)
{

    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());  //tutaj wczytujesz sobie caly dokument JSON
        QJsonObject root = document.object(); //tutaj wyciagasz ten dokument jako obiekt typu JSON

        double current_velocity = root.value("velocity").toDouble();
        qDebug() <<current_velocity ;
        //qDebug() << root.value("velocity");
        double  current_latitude= root.value("latitude").toDouble();
        qDebug() << root.value("latitude");
        double  current_longitude=root.value("longitude").toDouble();
        qDebug() << root.value("longitude");
        double current_altitude=root.value("altitude").toDouble();
        qDebug() << root.value("altitude");

a1=current_velocity;
a2=current_latitude;
a3=current_longitude;
a4=current_altitude;
        //szerokosc
        ui->textBrowser->setText(QString::number(current_latitude));
        //dlugosc
        ui->textBrowser_2->setText(QString::number(current_longitude));
        //wysokosc
        ui->textBrowser_3->setText(QString::number(current_altitude));
        //predkosc
        ui->textBrowser_4->setText(QString::number(current_velocity));


       }
    else if(reply->error()){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());  //tutaj wczytujesz sobie caly dokument JSON
        QJsonObject root = document.object(); //tutaj wyciagasz ten dokument jako obiekt typu JSON
        QString error=root.value("error").toString();
        qDebug() << root.value("error");


                ui->textBrowser->setText(error);
                ui->textBrowser_2->setText("ERROR- TOO MANY REQUESTS. PLEASE SHUT DOWN THE APPLICATION");
                ui->textBrowser_3->setText("ERROR- TOO MANY REQUESTS. PLEASE SHUT DOWN THE APPLICATION");
                ui->textBrowser_4->setText("ERROR- TOO MANY REQUESTS. PLEASE SHUT DOWN THE APPLICATION");


            if (error==0){ //to dziala
                ui->textBrowser->setText("ERROR- CONNECTION FALIED");
                ui->textBrowser_2->setText("ERROR- CONNECTION FALIED");
                ui->textBrowser_3->setText("ERROR- CONNECTION FALIED");
                ui->textBrowser_4->setText("ERROR- CONNECTION FALIED");
                }


    }
}






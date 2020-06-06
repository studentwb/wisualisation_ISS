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
    QObject::connect(this, SIGNAL(sendData_1(float)),ui->gWindow, SLOT(getData_1(float)));
    QObject::connect(this, SIGNAL(sendData_2(float)),ui->gWindow, SLOT(getData_2(float)));
    QObject::connect(this, SIGNAL(sendData_3(float)),ui->gWindow, SLOT(getData_3(float)));
    QObject::connect(this, SIGNAL(sendData_4(float)),ui->gWindow, SLOT(getData_4(float)));
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
        double  current_latitude= root.value("latitude").toDouble();
        double  current_longitude=root.value("longitude").toDouble();
        double current_altitude=root.value("altitude").toDouble();

        float a1=current_longitude;
        float a2=current_latitude;
        float a3=current_altitude;
        float a4=current_velocity;

        emit sendData_1(a1); //wywlouje funkcje, ktora ma byc sygnalem
        emit sendData_2(a2);
        emit sendData_3(a3);
        emit sendData_4(a4);

        //szerokosc
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit->setText(QString::number(current_latitude));
        //dlugosc
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_2->setText(QString::number(current_longitude));
        //wysokosc
        ui->lineEdit_3->setReadOnly(true);
        ui->lineEdit_3->setText(QString::number(current_altitude));
        //predkosc
        ui->lineEdit_4->setReadOnly(true);
        ui->lineEdit_4->setText(QString::number(current_velocity));


       }
    else if(reply->error()){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());  //tutaj wczytujesz sobie caly dokument JSON
        QJsonObject root = document.object(); //tutaj wyciagasz ten dokument jako obiekt typu JSON
        QString error=root.value("error").toString();
        qDebug() << root.value("error");

                ui->lineEdit_5->setReadOnly(true);
                ui->lineEdit_5->setText(error+" ERROR- TOO MANY REQUESTS. PLEASE SHUT DOWN THE APPLICATION");


            if (error==0){ //to dziala
                ui->lineEdit_5->setReadOnly(true);
                ui->lineEdit_5->setText("ERROR- CONNECTION FAILED");

                }

else{
                ui->lineEdit_5->setReadOnly(true);
                ui->lineEdit_5->setText(" ");}
    }
}






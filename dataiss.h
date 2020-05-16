#ifndef DATAISS_H
#define DATAISS_H

#include <QMainWindow>
#include <QObject>
#include <QtCore/QString>
#include <QtQml/QQmlListProperty>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QTime>

class dataISS : public QObject
{
public:
    explicit dataISS(QObject *parent = nullptr);

};

#endif // DATAISS_H

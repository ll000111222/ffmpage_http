#ifndef HTTPTOOLS_H
#define HTTPTOOLS_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QIODevice>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QDebug>

class HttpTools
{
public:
    HttpTools();

    int getRequestWithArray( QMap<QString,QString> map);
    QJsonObject postRequest(QMap<QString,QString> map);
    QJsonObject getJsonObjectFromString(const QString jsonString);
    QString getStringFromJsonObject(const QJsonObject& jsonObject);

};

#endif // HTTPTOOLS_H

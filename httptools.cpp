#include "httptools.h"

HttpTools::HttpTools()
{


}

int HttpTools::getRequestWithArray(QMap<QString,QString> map)
{
    QString paramStr = "";
    for (auto key : map.keys())
    {
        paramStr= paramStr+"&"+key+"="+map.value(key);
    }

    //生成对应的网络请求
    QNetworkRequest request;
    QString scheme = "http";
    QString serverAddr = "127.0.0.1";
    QString port = "9098";
    QString requestHeader = scheme + QString("://") + serverAddr + QString(":") + port;
    QString fullRequest = requestHeader + QString("/practicalExam/getClentCurExam?1=1"+paramStr);
    request.setUrl(QUrl(fullRequest));

    //获取错误
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        return reply->error();
    }

    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        return -1;
    }
    QJsonObject rootObj = jsonDoc.object();

    qDebug()<<this->getStringFromJsonObject(rootObj);

    QString codeStr = rootObj.value("code").toString();
    if (codeStr.compare("200") == 0)
    {
        //返回代码为200的时候证明请求成功对包含的结构数据进行处理
        if(rootObj.contains("result"))
        {
            qDebug()<<rootObj;
        }
        return 0;
    }
    else
    {
        //请求失败对对应的处理
        return codeStr.toInt();
    }
}


QJsonObject HttpTools::postRequest(QMap<QString,QString> map)
{

    //生成对应的网址请求
    QNetworkRequest request;
    QString scheme = "http";
    QString serverAddr = "127.0.0.1";
    QString port = "9098";
    QString requestHeader = scheme + QString("://") + serverAddr + QString(":") + port;
    QString fullRequest = requestHeader + "/practicalExam/getClentCurExam?1=1";
    request.setUrl(QUrl(fullRequest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //获取对应的参数数据
    QByteArray data;

    for (auto key : map.keys())
    {
        data.append(key+"=");
        data.append(map.value(key).toUtf8());
    }

    //发送请求
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request,data);
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        QJsonObject qjo ;
        qjo.insert("code",500);
        return qjo;
    }


    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        QJsonObject qjo ;
        qjo.insert("code",500);
        return qjo;
    }
    QJsonObject rootObj = jsonDoc.object();

    return rootObj;

    //    int codeStr = rootObj.value("code").toInt(0);
    //    qDebug()<<"code = "<<codeStr;
    //    if (codeStr ==200 )
    //    {
    //        //返回代码为200的时候证明请求成功对包含的结构数据进行处理
    //        if(rootObj.contains("result"))
    //        {
    //            qDebug()<<rootObj;
    //        }
    //        return 0;
    //    }
    //    else
    //    {
    //        //请求失败对对应的处理
    //        return codeStr;
    //    }
}


// QString >> QJson
QJsonObject HttpTools::getJsonObjectFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
// QJson >> QString
QString  HttpTools::getStringFromJsonObject(const QJsonObject& jsonObject){
    return QString(QJsonDocument(jsonObject).toJson());
}

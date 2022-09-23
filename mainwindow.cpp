#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <httptools.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList urls;
    urls << "c:/qttest/test.mp4";
    urls << "c:/qttest/123.mp4";
    urls << "rtsp://admin:admin123456@192.168.1.112:554";
    ui->cboxUrl->addItems(urls);
    ui->cboxUrl->setCurrentIndex(0);

    //    FFmpegThread *thread = ui->playWidget->getFFmpegThread();
    //    connect(thread, SIGNAL(sendCurTime(double)), this, SLOT(get_cur_time(double)));


    tcpClient = new ATcpClient("127.0.0.1", 11210);
    connect(tcpClient, SIGNAL(sendReceiveMsg(QByteArray)), this, SLOT(getSocketMessage(QByteArray)));


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnOpen_clicked()
{
    QString url = ui->cboxUrl->currentText().trimmed();
    ui->playWidget->setUrl(url);
    ui->playWidget->open();
}


void MainWindow::on_btnClose_clicked()
{
    ui->playWidget->close();

}



void MainWindow::on_btnPause_clicked()
{
    qDebug()<<"视频暂停";
    ui->playWidget->pause();
}

void MainWindow::get_cur_time(double curTime)
{
    qDebug()<<"get_cur_time = "<<curTime;
}

void MainWindow::getSocketMessage(QByteArray byteArray)
{
    qDebug() <<"getSocketMessage "<< QString::fromLocal8Bit(byteArray);
}


void MainWindow::on_pbGet_clicked()
{
    QMap<QString,QString> map;
    map.insert("ip","127.0.0.1");
    HttpTools *httpTools = new HttpTools;
    QJsonObject jsonObject =   httpTools->postRequest(map);
    QString url = jsonObject.value("data").toObject().value("flvStr").toString();

    ui->playWidget->setUrl(url);
    ui->playWidget->open();


}



void MainWindow::on_pushButton_clicked()
{

    //    QThread::sleep(1);
    tcpClient->sendData("aaaa");
}


void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
    tcpClient->doReConnect();

}


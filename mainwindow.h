#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <atcpclient.h>
#include <QMainWindow>
#include <QTimer>


namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnPause_clicked();

    void get_cur_time(double curTime);

    void getSocketMessage(QByteArray byteArray);


    void on_pbGet_clicked();

    void on_pushButton_clicked();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow *ui;
    QTimer *m_pTimer;
    ATcpClient *tcpClient;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "robot.h"
#include "dialogrobot.h"

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

    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_3_clicked();

    void requestFinished(QNetworkReply* reply);

    void on_pushButton_4_clicked();

    void updateRobots(Robot* r);

private:
    void configRobots(char* robotInfo);

private:
    Ui::MainWindow *ui;

    DialogRobot dlg;

    //存储钉钉机器人信息
    QList<Robot*> robots;

    //当前选择要发送消息的机器人
    int m_iCurrRobot;
};
#endif // MAINWINDOW_H

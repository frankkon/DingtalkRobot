#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robot.h"

#include <QMessageBox>
#include <QtDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#define MAX_LENGTH 1024
#define END_OF_FILE -1

static int lineNum = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_iCurrRobot(0)
{
    ui->setupUi(this);

    connect(&dlg, &DialogRobot::updateRobotsSignal, this, &MainWindow::updateRobots);

    on_pushButton_3_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(robots);
    robots.clear();
}


void MainWindow::on_pushButton_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    request.setUrl(QUrl(robots[m_iCurrRobot]->getUrl()));
    request.setRawHeader("Content-Type","application/json; charset=utf-8");

    QJsonObject content;
    QString buf = ui->textEdit->toPlainText() + "[" + robots[m_iCurrRobot]->getSign() + "]";
    qDebug() << buf;
    content.insert("content", buf);

    QJsonObject msg;
    msg.insert("msgtype","text");
    msg.insert("text", content);

    QByteArray postData = QJsonDocument(msg).toJson();
    naManager->post(request, postData);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(dlg.exec() != QDialog::Accepted)
    {
        qDebug() << "Open DialogRobot Failed";
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    m_iCurrRobot = index;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->comboBox->clear();
    qDeleteAll(robots);
    robots.clear();

    QFile f_robots("/Users/kongjun/Documents/MySrc/HelloQT/robots.cfg");
    if(!f_robots.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "打开文件失败，文件名：" << f_robots.fileName();
        return;
    }

    char buf[MAX_LENGTH+1] = {0};
    while (END_OF_FILE != f_robots.readLine(buf, MAX_LENGTH)) {
        configRobots(buf);
    }

    f_robots.close();
}

void MainWindow::configRobots(char* robotInfo)
{
    QString buf(robotInfo);
    QStringList qsBuf = buf.split(QLatin1Char('|'));
    Robot* robot = new Robot();
    robot->setName(qsBuf[0]);
    robot->setUrl(qsBuf[1]);
    robot->setSign(qsBuf[2]);
    robots.append(robot);
    ui->comboBox->addItem(robot->getName());

}

void MainWindow::requestFinished(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        ui->textEdit_2->append(QString::number(lineNum++) + ": " + reply->readAll());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    lineNum = 0;
    ui->textEdit_2->clear();
}

void MainWindow::updateRobots(Robot* r)
{
    ui->comboBox->addItem(r->getName());
    robots.append(r);

    QFile f_robots("/Users/kongjun/Documents/MySrc/HelloQT/robots.cfg");
    if(!f_robots.open(QFile::WriteOnly |QFile::Append | QFile::Text))
    {
        qDebug() << "打开文件失败，文件名：" << f_robots.fileName();
        return;
    }

    QTextStream in(&f_robots);
    in << Qt::endl << r->getName() << "|" << r->getUrl() << "|" << r->getSign() << "|";

    f_robots.close();
}

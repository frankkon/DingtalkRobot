#include "dialogrobot.h"
#include "ui_dialogrobot.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <QMessageBox>

DialogRobot::DialogRobot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRobot)
{
    ui->setupUi(this);
}

DialogRobot::~DialogRobot()
{
    delete ui;
}

void DialogRobot::on_pushButton_clicked()
{
    if(ui->lineEdit->text().trimmed() == ""
            || ui->lineEdit_2->text().trimmed() == ""
            || ui->lineEdit_3->text().trimmed() == "")
    {
        QMessageBox::warning(this, "提示", "请输入正确的钉钉机器人信息！");
        return;
    }

    Robot* r = new Robot();
    r->setName(ui->lineEdit->text());
    r->setUrl(ui->lineEdit_2->text());
    r->setSign(ui->lineEdit_3->text());

    emit updateRobotsSignal(r);

    this->close();
}

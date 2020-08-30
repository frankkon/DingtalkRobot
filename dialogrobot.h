#ifndef DIALOGROBOT_H
#define DIALOGROBOT_H

#include <QDialog>

#include "robot.h"

namespace Ui {
class DialogRobot;
}

class DialogRobot : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRobot(QWidget *parent = nullptr);
    ~DialogRobot();

signals:
    void updateRobotsSignal(Robot* r);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogRobot *ui;
};

#endif // DIALOGROBOT_H

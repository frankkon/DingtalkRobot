#include "robot.h"

Robot::Robot(QObject *parent) : QObject(parent)
{

}

QString Robot::getName()
{
    return m_sName;
}

QString Robot::getUrl()
{
    return m_sUrl;
}

QString Robot::getSign()
{
    return m_sSign;
}

void Robot::setName(QString name)
{
    m_sName = name;
}

void Robot::setUrl(QString url)
{
    m_sUrl = url;
}

void Robot::setSign(QString sign)
{
    m_sSign = sign;
}


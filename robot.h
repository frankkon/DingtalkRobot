#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = nullptr);

    QString getName();
    QString getUrl();
    QString getSign();

    void setName(QString name);
    void setUrl(QString url);
    void setSign(QString sign);

private:
    QString m_sName;
    QString m_sUrl;
    QString m_sSign;
signals:

};

#endif // ROBOT_H

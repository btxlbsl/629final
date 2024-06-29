#ifndef DATA_H
#define DATA_H

#include <QWidget>
#include"user.h"
#include<QFile>
#include<QDebug>
class data : public QWidget
{
    Q_OBJECT
public:
    explicit data(QWidget *parent = nullptr);
    static QList<user *> userList;
    static const QString savepath;
    static void Load_User();
    static void Write_User(user *u);
    static void Upgrade_User();
signals:
};

#endif // DATA_H

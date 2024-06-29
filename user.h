#ifndef USER_H
#define USER_H
#include<QObject>
class user
{
public:
    QString  username;
    QString password;
    QList<QString> playlist;
    user(QString password, QString username);
    user();
};
#endif // USER_H

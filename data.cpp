#include "data.h"

data::data(QWidget *parent): QWidget{parent}{}
QList<user*> data::userList;
const QString data::savepath = "userdata.txt";
void data::Load_User()
{
    data::userList.clear();
    QFile file(data::savepath);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(file.isOpen())
    {
        QTextStream in(&file);
        QString dt;
        QStringList userdt;
        while(!in.atEnd())
        {
                dt = in.readLine();
                userdt = dt.split(" ");
                user* in_user = new user(userdt.at(0), userdt.at(1));
                data::userList.push_back(in_user);
                userdt.clear();
        }
        file.close();
    }
}

void data::Upgrade_User()
{
    QFile file(data::savepath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    if(file.isOpen())
    {
        QTextStream in(&file);
        for(int i = 0;i<data::userList.size();++i)
        {
            in<<data::userList.at(i)->username<<" "<<data::userList.at(i)->password<<"\n";
        }
        file.close();
    }
}
void data::Write_User(user *u)
{
    QFile file(data::savepath);
    file.open(QIODevice::Append|QIODevice::Text);
    if(file.isOpen())
    {
        QTextStream in(&file);
        in<<u->username<<" "<<u->password<<"\n";
        file.close();
    }
}

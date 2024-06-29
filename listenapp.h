#ifndef LISTENAPP_H
#define LISTENAPP_H
#include<QObject>
#include"login.h"
#include"mainwindow.h"
#include"Register.h"
class listenapp:public QObject
{
public:
    listenapp();
    ~listenapp();
    login* lg;
    MainWindow* mw;
    Register* rg;

    void new_login();
    void new_mainwindows( QString _username);
    void login_success_slots( QString _username);
    void start_register_slots();
    void success_register_slots();
    void back_login_slots();
};

#endif // LISTENAPP_H

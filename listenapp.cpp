#include "listenapp.h"

listenapp::listenapp()
{
    lg = new login();
    lg->show();
    connect(lg, &login::login_success_signals, this, &listenapp::login_success_slots);
    connect(lg, &login::start_register_signals,this, &listenapp::start_register_slots);
}
listenapp::~listenapp()
{
    if(lg!=nullptr)
        delete lg;
    if(rg!=nullptr)
        delete rg;
    if(mw!=nullptr)
        delete mw;
}

void listenapp::new_mainwindows( QString username)
{
    mw = new MainWindow(username, nullptr);
    mw->show();
}
void listenapp::login_success_slots( QString _username)
{
    delete lg;lg = nullptr;
    new_mainwindows(_username);
}
void listenapp::start_register_slots()
{
    rg = new Register();
    rg->show();
    connect(rg, &Register::success_register_signal, this, &listenapp::success_register_slots);
    connect(rg,&Register::back_login_signal, this,&listenapp::back_login_slots);
}
void listenapp::success_register_slots()
{
    lg->show();
    data::Load_User();
}
void listenapp::back_login_slots()
{
    lg->show();
}

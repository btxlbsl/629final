#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent): QDialog(parent), ui(new Ui::login)
{
    ui->setupUi(this);
    data::Load_User();
}

login::~login()
{
    delete ui;
}

void login::on_LoginBtn_clicked()
{
    QString username = ui->UsnInput->text();
    QString password = ui->PswInput->text();
    if(find_user(username,password))
    {
        this->close();
        emit login_success_signals(username);
    }
    else
    {
        QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误!"),QMessageBox::Ok);
        ui->UsnInput->clear();
        ui->PswInput->clear();
        ui->UsnInput->setFocus();
    }
}

void login::on_Exit_btn_clicked()
{
    this->close();
}

bool login::find_user(QString _username,QString _password)
{
    for(int i=0;i<data::userList.size();++i)
    {
        if(data::userList.at(i)->username == _username&&data::userList.at(i)->password==_password)
        {
            return true;
        }
    }
    return false;
}


void login::on_RegisterBtn_clicked()
{
    this->close();
    emit start_register_signals();
}


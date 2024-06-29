#include "Register.h"
#include "ui_Register.h"
#include"data.h"
Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

}

Register::~Register()
{
    delete ui;
}

void Register::on_SureBtn_clicked()
{
    if(ui->UsnInput->text()!=""&&ui->PswInput->text() == ui->PswCheck->text())
    {
        QMessageBox::information(this,tr("注册成功"),tr("您成功完成了注册!"),QMessageBox::Ok);
        user* newuser = new user(ui->UsnInput->text(),ui->PswInput->text());
        data::Write_User(newuser);
        delete newuser;
        this->close();
        emit success_register_signal();
    }
    else if(ui->UsnInput->text()==""||ui->PswInput->text()=="")
    {
        QMessageBox::warning(this,tr("注册失败"),tr("用户名或密码不能为空!"),QMessageBox::Ok);
        ui->UsnInput->clear();
        ui->PswInput->clear();
        ui->PswCheck->clear();
        ui->UsnInput->setFocus();
    }
    else if(ui->PswInput->text() != ui->PswCheck->text())
    {
        QMessageBox::warning(this,tr("注册失败"),tr("两次输入的密码不一致!"),QMessageBox::Ok);
        ui->UsnInput->clear();
        ui->PswInput->clear();
        ui->PswCheck->clear();
        ui->UsnInput->setFocus();
    }
}


void Register::on_ExitBtn_clicked()
{
    this->close();
    emit back_login_signal();
}


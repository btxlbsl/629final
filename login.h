#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"data.h"
#include"Register.h"
#include <QMessageBox>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    bool find_user(QString username,QString password);
    ~login();

private slots:
    void on_LoginBtn_clicked();

    void on_Exit_btn_clicked();

    void on_RegisterBtn_clicked();

private:
    Ui::login *ui;
signals:
    void login_success_signals(QString _username);
    void start_register_signals();
};

#endif // LOGIN_H

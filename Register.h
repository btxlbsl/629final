#ifndef REGISTER_H
#define REGISTER_H
#include <QMessageBox>
#include <QDialog>
#include"user.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_SureBtn_clicked();
    void on_ExitBtn_clicked();

signals:
    void success_register_signal();
    void back_login_signal();
private:
    Ui::Register *ui;
};

#endif // REGISTER_H

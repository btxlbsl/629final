#include "set_skin.h"
#include "ui_set_skin.h"
#include <QLabel>
#include <QPixmap>
#include"mainwindow.h"
set_skin::set_skin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::set_skin)
{
    ui->setupUi(this);
    skin();

}

set_skin::~set_skin()
{
    delete ui;
}
void set_skin::skin()
{
    ui->listWidget->addItem("white");
    ui->listWidget->addItem("black");
}

void set_skin::put_picture(QString a)
{
    QPixmap pixmap(a);
    ui->label->clear();
    ui->label->setScaledContents(true);
    ui->label->setPixmap(pixmap);
    ui->label->show();
}


void set_skin::on_listWidget_doubleClicked(const QModelIndex &index)
{
    switch(index.row())
    {
    case 0:
        a=":/image/images/white.png";
        set_skin::put_picture(a);
        break;
    case 1:
        a=":/image/images/black.png";
        set_skin::put_picture(a);
        break;
    }
}


void set_skin::on_buttonBox_accepted()
{
    emit change_pifu_signals(a);
}


void set_skin::on_buttonBox_rejected()
{
    emit change_pifu_signals("");
}


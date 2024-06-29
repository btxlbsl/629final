#include "yibofang.h"
#include "ui_yibofang.h"

yibofang::yibofang(QWidget *parent, QStringList data)
    : QWidget(parent)
    , ui(new Ui::yibofang)
{
    ui->setupUi(this);
     lstdata = data;
    picture();
    list_bofang();
}
void yibofang::list_bofang()
{
    for(int i=lstdata.size()-1;i>=0;--i)
    {
        ui->listWidget->addItem(lstdata[i]);
    }
}

yibofang::~yibofang()
{
    delete ui;
}


void yibofang::on_listWidget_doubleClicked(const QModelIndex &index)
{
    wantplay = ui->listWidget->itemFromIndex(index)->text();
    emit play_haveplayed_signal(wantplay);
}

void yibofang::picture()
{
    QPixmap pixmap(":/image/images/haveplay.jpg");
    ui->love_songs->clear();
    ui->love_songs->setScaledContents(true);
    ui->love_songs->setPixmap(pixmap);
    ui->love_songs->show();
}


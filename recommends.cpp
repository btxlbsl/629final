#include "recommends.h"
#include "ui_recommends.h"

#
recommends::recommends(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::recommends)
{
    ui->setupUi(this);
    picture();
    list_songs();
}

recommends::~recommends()
{
    delete ui;
}

void recommends::picture()
{
    QPixmap pixmap(":/image/images/guessyoulove.png");
    ui->love_songs->clear();
    ui->love_songs->setScaledContents(true);
    ui->love_songs->setPixmap(pixmap);
    ui->love_songs->show();
}

void recommends::list_songs()
{
    int randomInt[5];
    int k=0;
    int x;
    QString morenpath = "E:/qt_homework/test1/music_resource";
    qInfo()<<morenpath;
    QDir dir(morenpath);
    auto musicList = dir.entryList(QStringList()<<"*.flac");
    totalnum = musicList.length();
    bool flag;
    while(k<5)
    {
        flag=0;
        x=QRandomGenerator::global()->bounded(totalnum);
        for(int i=0;i<k;i++) if(x==randomInt[i]) {flag=1;break;}
        if(flag) continue;
        randomInt[k]=x;
        ui->List_songs->addItem(musicList[x]);
        k++;
    }
}

void recommends::on_List_songs_doubleClicked(const QModelIndex &index)
{
    song_name = ui->List_songs->itemFromIndex(index)->text();

    emit play_music_signal(song_name);
}


void recommends::on_closeBtn_clicked()
{
    this->close();
    emit close_recommend_signal();
}


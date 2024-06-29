#include "search.h"
#include "ui_search.h"

search::search(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::search)
{
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}

void search::on_searchBtn_clicked()
{
    singer[0]=ui->singer0;
    singer[1]=ui->singer1;
    singer[2]=ui->singer2;
    singer[3]=ui->singer3;
    singer[4]=ui->singer4;
    song[0]=ui->song0;
    song[1]=ui->song1;
    song[2]=ui->song2;
    song[3]=ui->song3;
    song[4]=ui->song4;
    face[0]=ui->face0;
    face[1]=ui->face1;
    face[2]=ui->face2;
    face[3]=ui->face3;
    face[4]=ui->face4;
    QString name = ui->lineEdit->text();
    QDir dir(":/music/music_resource");
    auto musicList = dir.entryList(QStringList()<<"*.flac");
    auto piclist = dir.entryList(QStringList()<<"*.webp");
    QStringList list;

    int num=0;
    for(int i=0;i<musicList.size();++i)
    {
        if(musicList[i].contains(name))
        {
            list = piclist[i].split(' ');
            song[num]->setText(list[0]);
            singer[num]->setText(list[2].left(list[2].size()-5));
            QPixmap pixmap(":/music/music_resource/"+piclist[i]);
            face[num]->setScaledContents(true);
            face[num]->setPixmap(pixmap);
            num++;
            list.clear();
            if(num==5) break;
        }
    }
}


void search::on_closeBtn_clicked()
{
    this->close();
    emit close_search_signals();
}
void search::on_pushButton_1_clicked()
{
    if(!song[0]) return;
    s = song[0]->text()+" - "+singer[0]->text();
    emit search_song_name(s);
}


void search::on_pushButton_2_clicked()
{
    if(!song[1]) return;
    s = song[1]->text()+" - "+singer[1]->text();
    emit search_song_name(s);
}


void search::on_pushButton_3_clicked()
{
    if(!song[2]) return;
    s = song[2]->text()+" - "+singer[2]->text();
    emit search_song_name(s);
}


void search::on_pushButton_4_clicked()
{
    if(!song[3]) return;
    s = song[3]->text()+" - "+singer[3]->text();
    emit search_song_name(s);
}


void search::on_pushButton_5_clicked()
{
    if(!song[4]) return;
    s = song[4]->text()+" - "+singer[4]->text();
    emit search_song_name(s);
}


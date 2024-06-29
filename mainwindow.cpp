#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QString _username,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),username(_username)
{
    ui->setupUi(this);
    curPlayIndex = 0;
    sumSong = 0;
    audioOutput = new QAudioOutput(this);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);

    QPixmap pixmap(":/new/prefix1/icons/chazhao.png");
    pixmap = pixmap.scaled(QSize(15, 15), Qt::KeepAspectRatio);
    ui->lyric->setFont(QFont("楷体",15));
    ui->lyric->setText("您目前未播放音乐");

    //获取当前媒体的时长，通过信号关联获取总音乐时长
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration)
            {
                ui->totallabel->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
                ui->playCourseSlider->setRange(0,duration);    //让进度滑块随时间动起来(1)
            });
    //获取当前播放时长
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 pos)
            {
                ui->curlabel->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));
                ui->playCourseSlider->setValue(pos);          //让进度滑块随时间动起来(2)
            });
    //拖动滑块改变播放进度
    connect(ui->playCourseSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);
    audioOutput->setVolume(0.5);

    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::update_lyrics);


    qInfo()<<morenpath;
    QDir dir(morenpath);
    auto musicList = dir.entryList(QStringList()<<"*.flac");
    auto piclist = dir.entryList(QStringList()<<"*.webp");
    auto lyriclist = dir.entryList(QStringList()<<"*.lrc");
    qInfo()<<musicList;
    ui->song_name->setText(musicList[0]);
    ui->song_pic->setPixmap(QPixmap(morenpath + "/" +piclist[0]));
    parseLyrics(morenpath+"/" +lyriclist[0]);
    for(const auto &file : musicList)
    {
        playList.append(QUrl::fromLocalFile(morenpath+"/"+file));
        sumSong++;
    }
    for(const auto &file : piclist)
    {
        picList.append(QUrl::fromLocalFile(morenpath+"/" + file));
    }
    for(const auto &file:lyriclist)
    {
        lyricList.append(QUrl::fromLocalFile(morenpath+"/"+file));
    }

}
int MainWindow::model = 0;
bool MainWindow::slience = false;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stop_clicked()
{
    if(playList.empty())
    {
        return;
    }
    QIcon start(":/new/prefix1/icons/zanting.png");
    QIcon pause(":/new/prefix1/icons/bofang.png");
    switch(mediaPlayer->playbackState())
    {
    case QMediaPlayer::StoppedState://停止状态
    {
        //如果没有播放，播放当前选中的音乐
        mediaPlayer->setSource(playList[curPlayIndex]);
        mediaPlayer->play();
        ui->stop->setIcon(start);
        append_yibofang(playList[curPlayIndex].fileName());
        break;
    }
    case QMediaPlayer::PlayingState://播放状态
        //如果正在播放，暂停音乐
        mediaPlayer->pause();
        ui->stop->setIcon(pause);
        break;
    case QMediaPlayer::PausedState://暂停状态
        //如果正在暂停，继续播放
        mediaPlayer->play();
        ui->stop->setIcon(start);
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(this->Pfpath));
}


void MainWindow::on_volume_clicked()
{
    QIcon mute(":/new/prefix1/icons/jingyin.png");
    QIcon neg_mute(":/new/prefix1/icons/yinliang.png");
    if(MainWindow::slience) //切换到非静音
    {
        ui->volume->setIcon(neg_mute);
        MainWindow::slience = false;
        audioOutput->setVolume(20);
    }
    else //静音
    {
        ui->volume->setIcon(mute);
        MainWindow::slience = true;
        audioOutput->setVolume(0);
    }
}


void MainWindow::on_playmode_clicked()
{
    MainWindow::model++;
    if(MainWindow::model%2==0) //顺序播放
    {
        ui->playmode->setIcon(QIcon(":/new/prefix1/icons/shunxubofang.png"));

    }
    else if (MainWindow::model%2==1) //单曲循环
    {
        ui->playmode->setIcon(QIcon(":/new/prefix1/icons/danquxunhuan.png"));
    }
}


void MainWindow::on_file_clicked()
{
    sumSong = 0;
    playList.clear();
    lyricList.clear();
    picList.clear();
    QListWidget *listWidget = findChild<QListWidget *>("listWidget");
    if(listWidget)
    {
        listWidget->show();
    }
    auto path = QFileDialog::getExistingDirectory(this,"请选择音乐所在的目录","C:\\");
    qInfo()<<path;
    if(path=="")
        return;
    QDir dir(path);
    auto musicList = dir.entryList(QStringList()<<"*.flac");
    auto piclist = dir.entryList(QStringList()<<"*.webp");
    auto lyriclist = dir.entryList(QStringList()<<"*.lrc");
    qInfo()<<musicList;

    ui->song_name->setText(musicList[0]);
    ui->song_pic->setPixmap(QPixmap(path + "/" +piclist[0]));
    parseLyrics(path+"/" +lyriclist[0]);
    for(const auto &file : musicList)
    {
        playList.append(QUrl::fromLocalFile(path+"/"+file));
        sumSong++;
    }
    for(const auto &file : piclist)
    {
        picList.append(QUrl::fromLocalFile(path+"/" + file));
    }
    for(const auto &file:lyriclist)
    {
        lyricList.append(QUrl::fromLocalFile(path+"/"+file));
    }

}

//歌词
void MainWindow::parseLyrics(const QString &filePath)
{

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpression re("\\[(\\d{2}):(\\d{2})\\.(\\d{2})\\](.*)");
        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            int minutes = match.captured(1).toInt();
            int seconds = match.captured(2).toInt();
            int milliseconds = match.captured(3).toInt() * 10;
            QTime time(0, minutes, seconds, milliseconds);
            QString text = match.captured(4);
            songlyrics.insert(time, text);
        }
    }

}
void MainWindow::loadLyricsForSong(const QString &filePath)
{
    songlyrics.clear();
    parseLyrics(filePath);
}
void MainWindow::update_lyrics(qint64 position)
{
    QTime currentTime = QTime(0, 0).addMSecs(position);
    auto it = songlyrics.lowerBound(currentTime);
    if (it != songlyrics.begin())
    {
        --it;
    }
    ui->lyric->setText(it.value());
}

void MainWindow::on_volume_bar_valueChanged(int value)
{
    audioOutput->setVolume(float(value)/100);
}

void MainWindow::change_pifu_slot(QString a)
{
    delete skin;
    this->Pfpath = a;

    if(a!="")
        this->repaint();
}

void MainWindow::on_pifu_clicked()
{
    skin = new set_skin();
    skin->show();
    connect(skin, &set_skin::change_pifu_signals, this, &MainWindow::change_pifu_slot);

}

void MainWindow::append_yibofang(QString s)
{
    for(int i=0;i<have_played.size();++i)
    {
        if(have_played[i] == s)
        {
            if(i!=have_played.size()-1)
            {
                have_played.takeAt(i);
                have_played.append(s);
                return;
            }
        }
    }
    if(have_played.size()==10)
    {
        have_played.pop_front();
        have_played.append(s);
    }
    else
    {
        have_played.append(s);
    }
}

void MainWindow::on_next_clicked() // 下一首
{
    if(playList.empty())
    {
        return;
    }
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState || mediaPlayer->playbackState() == QMediaPlayer::PausedState) {
        mediaPlayer->stop();
    }

    if (MainWindow::model%2==1)
    {
    }
    else
    {
    curPlayIndex=(curPlayIndex+1) % sumSong;
    }
    loadLyricsForSong(":/music/music_resource/" + lyricList[curPlayIndex].fileName());
    ui->song_name->setText(playList[curPlayIndex].fileName());
    ui->song_pic->setPixmap(QPixmap(":/music/music_resource/" + picList[curPlayIndex].fileName()));
    mediaPlayer->setSource(playList[1]);
    mediaPlayer->setSource(playList[curPlayIndex]);
    ui->stop->setIcon(QIcon(":/new/prefix1/icons/zanting.png"));
    mediaPlayer->play();
    append_yibofang(playList[curPlayIndex].fileName());
}

void MainWindow::on_pre_clicked() // 上一首
{
    if(playList.empty())
    {
        return;
    }
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState || mediaPlayer->playbackState() == QMediaPlayer::PausedState) {
        mediaPlayer->stop();
    }

    if (MainWindow::model%2==1)
    {
    }
    else
    {
        curPlayIndex=(curPlayIndex-1+ sumSong) % sumSong;
    }
    loadLyricsForSong(":/music/music_resource/" +lyricList[curPlayIndex].fileName());
    ui->song_name->setText(playList[curPlayIndex].fileName());
    ui->song_pic->setPixmap(QPixmap(":/music/music_resource/" +picList[curPlayIndex].fileName()));
    mediaPlayer->setSource(playList[1]);
    mediaPlayer->setSource(playList[curPlayIndex]);
    ui->stop->setIcon(QIcon(":/new/prefix1/icons/zanting.png"));
    mediaPlayer->play();

     append_yibofang(playList[curPlayIndex].fileName());
}

void MainWindow::close_recommed_slot()
{
    delete rec;rec = nullptr;
}
void MainWindow::on_dailyrec_clicked()
{
    rec = new recommends();
    rec->show();
    connect(rec,&recommends::close_recommend_signal, this, &MainWindow::close_recommed_slot);
    connect(rec,&recommends::play_music_signal, this,&::MainWindow::play_recmmed_slot);
}

void MainWindow::play_recmmed_slot(QString s)
{
    for(int i=0;i<sumSong;++i)
    {
        QString tmp = playList[i].fileName();
        if(tmp  == s)
        {
            curPlayIndex = i;
            break;
        }
    }
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState || mediaPlayer->playbackState() == QMediaPlayer::PausedState) {
        mediaPlayer->stop();
    }
    loadLyricsForSong(":/music/music_resource/" +lyricList[curPlayIndex].fileName());
    ui->song_name->setText(playList[curPlayIndex].fileName());
    ui->song_pic->setPixmap(QPixmap(":/music/music_resource/" +picList[curPlayIndex].fileName()));
    mediaPlayer->setSource(playList[curPlayIndex]);
    ui->stop->setIcon(QIcon(":/new/prefix1/icons/zanting.png"));
    mediaPlayer->play();
    append_yibofang(s);
    //close_recommed_slot();

}

void MainWindow::close_search_slot()
{
    delete rm;rm = nullptr;
}

void MainWindow::on_searchButton_clicked()
{
    rm = new search();
    rm->show();
    connect(rm, &search::close_search_signals,this,&MainWindow::close_search_slot);
    connect(rm,&search::search_song_name, this, &MainWindow::search_song_play_slot);
}

void MainWindow::search_song_play_slot(QString  s) //播放搜索得到的歌曲
{
    QString ts = s + ".flac";
    for(int i=0;i<sumSong;++i)
    {
        QString tmp = playList[i].fileName();
        if(tmp  == ts)
        {
            curPlayIndex = i;
            break;
        }
    }
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState || mediaPlayer->playbackState() == QMediaPlayer::PausedState) {
        mediaPlayer->stop();
    }
    loadLyricsForSong(":/music/music_resource/" +lyricList[curPlayIndex].fileName());
    ui->song_name->setText(playList[curPlayIndex].fileName());
    ui->song_pic->setPixmap(QPixmap(":/music/music_resource/" +picList[curPlayIndex].fileName()));
    mediaPlayer->setSource(playList[curPlayIndex]);
    ui->stop->setIcon(QIcon(":/new/prefix1/icons/zanting.png"));
    mediaPlayer->play();
    append_yibofang(ts);
    close_search_slot();
}

void MainWindow::play_haveplayed_slot(QString s)
{
    for(int i=0;i<sumSong;++i)
    {
        QString tmp = playList[i].fileName();
        if(tmp  == s)
        {
            curPlayIndex = i;
            break;
        }
    }
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState || mediaPlayer->playbackState() == QMediaPlayer::PausedState) {
        mediaPlayer->stop();
    }
    loadLyricsForSong(":/music/music_resource/" +lyricList[curPlayIndex].fileName());
    ui->song_name->setText(playList[curPlayIndex].fileName());
    ui->song_pic->setPixmap(QPixmap(":/music/music_resource/" +picList[curPlayIndex].fileName()));
    mediaPlayer->setSource(playList[curPlayIndex]);
    ui->stop->setIcon(QIcon(":/new/prefix1/icons/zanting.png"));
    mediaPlayer->play();

    append_yibofang(s);

    //close_songlst_slot();
}
void MainWindow::on_songlst_clicked()
{
    yb = new yibofang(nullptr, have_played);
    yb->show();
    connect(yb, &yibofang::close_yibo_signal, this, &MainWindow::close_songlst_slot);
    connect(yb,&yibofang::play_haveplayed_signal,this,&MainWindow::play_haveplayed_slot);
}
void MainWindow::close_songlst_slot()
{
    delete yb;yb = nullptr;
}

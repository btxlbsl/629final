#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QFileDialog>
#include<QListWidget>
#include<QAudioOutput>
#include <QDir>
#include<QUrl>
#include <QMap>
#include<QTimer>
#include<QTime>
#include<QTextStream>
#include<QRegularExpression>
#include<QPainter>
#include<QPaintEvent>
#include"set_skin.h"
#include"recommends.h"
#include"search.h"
#include"yibofang.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static bool slience;
    static int model;
    MainWindow(QString username,QWidget *parent = nullptr);
    ~MainWindow();
    void update_lyrics(qint64 position);
    void parseLyrics(const QString &filePath);
    void loadLyricsForSong(const QString &filePath);
     void paintEvent(QPaintEvent *e) override;
    void close_recommed_slot();
     void close_search_slot();
private slots:
    void on_stop_clicked();

    void on_volume_clicked();

    void on_playmode_clicked();

    void on_file_clicked();

    void on_pifu_clicked();

    void on_volume_bar_valueChanged(int value);

    void on_next_clicked();

    void change_pifu_slot(QString a);


    void on_dailyrec_clicked();

    void on_pre_clicked();

    void on_searchButton_clicked();

    void search_song_play_slot(QString s);

    void on_songlst_clicked();

    void close_songlst_slot();

    void play_recmmed_slot(QString s);

    void append_yibofang(QString s);

    void play_haveplayed_slot(QString s);
private:
    QString username;
    Ui::MainWindow *ui;
    QString morenpath = "E:/qt_homework/test1/music_resource";
    QList<QUrl> playList;
    QList<QUrl> picList;
    QList<QUrl> lyricList;
    QAudioOutput* audioOutput;
    QMediaPlayer* mediaPlayer;
    int curPlayIndex;
    int sumSong;
    QMap<QTime, QString> songlyrics;
    set_skin * skin;
    recommends * rec;
    search * rm;
    yibofang *yb;
    QString Pfpath = ":/image/images/white.png";
    QStringList have_played;
};
#endif // MAINWINDOW_H

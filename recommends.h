#ifndef RECOMMENDS_H
#define RECOMMENDS_H
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include<QDir>
#include<QRandomGenerator>
namespace Ui {
class recommends;
}

class recommends : public QDialog
{
    Q_OBJECT

public:
    explicit recommends(QWidget *parent = nullptr);
    ~recommends();
    void picture();
    void list_songs();
    int totalnum;
    QString song_name;


private slots:
    void on_List_songs_doubleClicked(const QModelIndex &index);

    void on_closeBtn_clicked();

signals:
    void close_recommend_signal();
    void play_music_signal(QString song_name);
private:
    Ui::recommends *ui;
};

#endif // RECOMMENDS_H

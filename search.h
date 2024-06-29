#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include<QLabel>
#include<QDir>
namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT
    QLabel* singer[5];
    QLabel* song[5];
    QLabel* face[5];
    QString s;
public:
    explicit search(QWidget *parent = nullptr);
    ~search();

private slots:
    void on_searchBtn_clicked();

    void on_closeBtn_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

signals:
    void close_search_signals();
    void search_song_name(QString s);
private:
    Ui::search *ui;
};

#endif // SEARCH_H

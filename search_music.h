#ifndef SEARCH_MUSIC_H
#define SEARCH_MUSIC_H

#include <QWidget>

namespace Ui {
class Search_music;
}

class Search_music : public QWidget
{
    Q_OBJECT

public:
    explicit Search_music(QWidget *parent = nullptr);
    ~Search_music();

private:
    Ui::Search_music *ui;
};

#endif // SEARCH_MUSIC_H
